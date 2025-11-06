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