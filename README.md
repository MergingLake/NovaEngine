# NovaEngine
This is a compilation of the classes covered in the subject of 3D Computational Graphics.

# How 3D Models Are Loaded?
This is the step-by-step flow:

### 1. `ModelLoader`

The `ModelLoader` has a single task: **to read an `.obj` file and "translate" it** into a format the engine can understand.

* **Input:** Receives a file path (e.g., `"models/MyModel"`).
* **Process:**
    1.  It automatically appends the `.obj` extension (e.g., `"models/MyModel.obj"`).
    2.  It opens and reads the text file line by line.
    3.  It parses the raw data: positions (`v`), texture coordinates (`vt`), and normals (`vn`).
    4.  It **intelligently** processes the faces (`f`) to build the final vertex list. It handles the triangulation of 4-sided faces (*quads*) and ensures correct vertex indexing so the model doesn't "break."
* **Output:** It doesn't create anything on the graphics card. It simply **fills the vectors** of a `MeshComponent` with the geometry it just read.

### 2. `MeshComponent`

The `MeshComponent` serves as a **data container on the CPU**.

* It's a class that holds two main lists (vectors): `m_vertex` (the vertices) and `m_index` (the indices).
* It starts empty.
* The `ModelLoader` is responsible for filling these lists.
* At this point, the 3D model exists **entirely in temporary memory**.

### 3. `BaseApp`

The `BaseApp` acts as the **coordinator** that manages the entire process during initialization (`init()`):

1.  First, `BaseApp` tells the `ModelLoader`: "Take this empty `MeshComponent` and fill it using this file: `"models/MyModel"`."
2.  Once the `ModelLoader` finishes, `BaseApp` has a `MeshComponent` filled with data on the CPU.
3.  Now, `BaseApp` turns to the buffers and tells them: "Take this filled `MeshComponent` and prepare it for the GPU."

### 4. `Buffer`

The `Buffer` class is the **bridge between the CPU and the GPU**.

1.  `BaseApp` calls `m_vertexBuffer.init(..., m_mesh)`.
2.  The `Buffer` class takes the data from `m_mesh.m_vertex`.
3.  It communicates with DirectX and **uploads that vertex list to the graphics card's memory**.
4.  `BaseApp` repeats this with `m_indexBuffer.init(..., m_mesh)` to upload the index list.

### 5. In the End

* The `BaseApp` no longer needs to worry about files or lists.
* It simply tells DirectX: "Activate the *vertex buffer* already on the GPU" and "Activate the *index buffer* already on the GPU."
* Finally, it executes the draw command (`DrawIndexed()`), using the data that already lives in the graphics card's fast memory.

**In summary: `ModelLoader` (reads) ➔ `MeshComponent` (stores in CPU) ➔ `Buffer` (uploads to GPU) ➔ `Render` (draws from GPU).**

# Core Systems Architecture (Runtime, Scripting & Physics)

The engine features a fully integrated runtime environment with Lua scripting and a custom physics solver, built on a strict Entity-Component-System (ECS) architecture.

### 1. State Management (Editor vs. Runtime)
To prevent runtime simulations from permanently mutating the level design, the engine strictly separates Editor and Play states.
* **Serialization-Based Reset:** Upon entering `EngineState::PLAY`, the engine serializes the current Scene Graph into a temporary disk backup (`PlayModeBackup.wvscene`).
* **Memory Cleanup:** When returning to `EngineState::EDITOR`, the engine flushes the current actors from memory and deserializes the backup. This approach prevents memory leaks and leftover references compared to manual frame-by-frame undo systems.
* **Pause State:** During `EngineState::PAUSED`, the physics and script update loops bypass the `deltaTime` execution, freezing the simulation in place while keeping the ImGui inspector and editor camera fully active for debugging.

### 2. Lua 5.4 Scripting via Sol2
The engine integrates Lua 5.4 to allow rapid gameplay prototyping without recompiling C++ source code.
* **C++ Binding (`sol::usertype`):** Native C++ classes (`Vector3`, `Transform`) are explicitly bound to the Lua virtual machine (`sol::state`). This allows Lua scripts to safely call underlying C++ memory addresses and methods (e.g., `transform:setPosition()`).
* **Sandboxed Environments:** The `LuaScriptComponent` assigns a unique `sol::environment` to every script instance. This prevents global scope pollution, ensuring that local variables in one script do not overwrite variables in another instance of the same script.
* **Update Cycle:** Scripts expose `Start()` and `Update(deltaTime)` hooks, which are dynamically cached via `sol::function` to prevent performance overhead during the main loop lookup.

### 3. Custom Physics & Collision Solver
Instead of relying strictly on external bloatware for simple needs, the engine features a native Rigid Body system based on the **Minimum Translation Vector (MTV)** algorithm.
* **Decoupled Components:** Physics logic is strictly separated. `BoxColliderComponent` acts as pure data (extents, offsets), while `RigidbodyComponent` handles forces, mass, and velocity. Static objects (like floors) utilize Colliders without Rigidbodies.
* **Predictive AABB:** Collisions are evaluated predictively. The engine calculates a `nextPos` based on velocity and `deltaTime`. If an AABB intersection is detected in the future frame, the engine calculates the overlap across all 3 axes.
* **MTV Resolution:** The engine compares `overlapX`, `overlapY`, and `overlapZ` to find the path of least resistance. It translates the object out of the collision exclusively along the axis with the minimum penetration, allowing for smooth wall sliding without teleportation bugs.
* **DeltaTime Clamping:** To prevent the infamous "Tunneling" effect caused by window lagging or pausing, the physics step features a clamp. If `deltaTime` exceeds `50ms`, the physics solver forces a `16ms` (~60 FPS) step to maintain mathematical stability.
* **Constraints:** Built-in bit-flags allow freezing translation and rotation along specific axes (similar to Unity's Rigidbody constraints), applying positional resets right before the final Transform matrix update.