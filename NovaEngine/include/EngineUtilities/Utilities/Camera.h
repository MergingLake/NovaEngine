#pragma once
#include "Prerequisites.h"
#include "EngineUtilities\Vectors\Vector3.h"

/* 
	@class Camera
	@brief A class that represents a camera in a 3D scene, responsible for managing the view and projection matrices.
	@note The Camera class provides functionality for setting up perspective projection, defining the camera's position and orientation, and calculating the view matrix based on the camera's basis vectors. It also includes methods for moving and rotating the camera, as well as retrieving the view and projection matrices for rendering.
*/
class
	Camera {
public:
	/* 
		@brief Default constructor that initializes the camera's position, basis vectors, and matrices to default values.
	*/
	Camera();
	/* 
		@brief Destructor
	*/
	~Camera() = default;

	/* 
		@brief Initializes the camera with default parameters.
	*/
	void
		setLens(float fovYRadians, float aspectRatio, float nearPlane, float farPlane);

	/* 
		@brief Sets the position of the camera in world space.
		@param x The x-coordinate of the camera's position.
		@param y The y-coordinate of the camera's position.
		@param z The z-coordinate of the camera's position.
	*/
	void
		setPosition(float x, float y, float z);

	/* 
		@brief Sets the position of the camera in world space using a Vector3.
		@param pos A Vector3 representing the camera's position in world space.
	*/
	void
		setPosition(const EU::Vector3& pos);

	/* 
		@brief Retrieves the current position of the camera in world space.
		@return A Vector3 representing the camera's position in world space.
	*/
	EU::Vector3
		getPosition() const { return m_position; }

	/* 
		@brief Defines the camera's orientation and view matrix based on a target point and an up vector.
		@param pos The position of the camera in world space.
		@param target The point in world space that the camera is looking at.
		@param up The up vector that defines the camera's vertical orientation (default is (0, 1, 0)).
	*/
	void
		lookAt(const EU::Vector3& pos,
			const EU::Vector3& target,
			const EU::Vector3& up = EU::Vector3(0, 1, 0));

	/* 
		@brief Moves the camera forward or backward along its forward vector.
		@param d The distance to move the camera. Positive values move the camera forward, while negative values move it backward.
	*/
	void
		walk(float d);

	/* 
		@brief Moves the camera left or right along its right vector.
		@param d The distance to move the camera. Positive values move the camera to the right, while negative values move it to the left.
	*/
	void
		strafe(float d);

	/* 
		@brief Moves the camera up or down along its up vector.
		@param d The distance to move the camera. Positive values move the camera up, while negative values move it down.
	*/
	void
		yaw(float radians);

	/* 
		@brief Rotates the camera around its right vector (pitch).
		@param radians The angle in radians to rotate the camera. Positive values pitch the camera up, while negative values pitch it down.
	*/
	void
		pitch(float radians);

	/* 
		@brief Rotates the camera around its forward vector (roll).
		@param radians The angle in radians to rotate the camera. Positive values roll the camera to the right, while negative values roll it to the left.
	*/
	void
		updateViewMatrix();

	/* 
		@brief Retrieves the current view matrix of the camera.
		@return An XMMATRIX representing the camera's view transformation.
	*/
	XMMATRIX
		getView() const { return XMLoadFloat4x4(&m_view); }

	/* 
		@brief Retrieves the current projection matrix of the camera.
		@return An XMMATRIX representing the camera's projection transformation.
	*/
	XMMATRIX
		getProj() const { return XMLoadFloat4x4(&m_proj); }

	/* 
		@brief Retrieves the view matrix of the camera without the translation component.
		@return An XMMATRIX representing the camera's view transformation without translation.
	*/
	XMMATRIX
		GetViewNoTranslation() const {
		XMMATRIX v = getView();
		// Quitar traslación (fila 4)
		v.r[3] = XMVectorSet(0, 0, 0, 1);
		return v;
	}

	/* 
		@brief Retrieves the camera's field of view (FOV) angle in radians.
		@return The field of view (FOV) angle in radians.
	*/
	float getFovY()   const { return m_fovY; }
	/* 
		@brief Retrieves the camera's aspect ratio (width divided by height).
		@return The aspect ratio of the camera's view.
	*/
	float getAspect() const { return m_aspectRatio; }
	/*
		@brief Retrieves the distance to the near clipping plane.
		@return The distance to the near clipping plane.
	*/
	float getNearZ()  const { return m_nearPlane; }
	/* 
		@brief Retrieves the distance to the far clipping plane.
		@return The distance to the far clipping plane.
	*/
	float getFarZ()   const { return m_farPlane; }

	/* 
		@brief Retrieves the right vector of the camera's orthonormal basis.
		@return A Vector3 representing the right vector of the camera.
	*/
	EU::Vector3 GetRight()   const { return m_right; }
	/* 
		@brief Retrieves the up vector of the camera's orthonormal basis.
		@return A Vector3 representing the up vector of the camera.
	*/
	EU::Vector3 GetUp()      const { return m_up; }
	/* 
		@brief Retrieves the forward vector of the camera's orthonormal basis.
		@return A Vector3 representing the forward vector of the camera.
	*/
	EU::Vector3 GetForward() const { return m_forward; }

	/* 
		@brief Converts an XMVECTOR to a Vector3 by extracting the x, y, and z components.
		@param v The XMVECTOR to convert.
		@return A Vector3 containing the x, y, and z components of the input XMVECTOR.
	*/
	inline EU::Vector3
		FromXM(FXMVECTOR v) {
		XMFLOAT3 t;
		XMStoreFloat3(&t, v);
		return EU::Vector3(t.x, t.y, t.z);
	}


private:
	// Estado espacial
	EU::Vector3 m_position; /**< The position of the camera in world space. */

	// Basis Ortonormal (en mundo)
	EU::Vector3 m_right{ 1.0f, 0.0f, 0.0f }; /**< The right vector of the camera's orthonormal basis. */
	EU::Vector3 m_up{ 0.0f, 1.0f, 0.0f }; /**< The up vector of the camera's orthonormal basis. */
	EU::Vector3 m_forward{ 0.0f, 0.0f, 1.0f }; /**< The forward vector of the camera's orthonormal basis. */

	// Matrices almacenadas
	XMFLOAT4X4 m_view{};
	XMFLOAT4X4 m_proj{};

	// Parametros de la proyeccion
	float m_fovY{ XM_PIDIV4 }; /**< The field of view (FOV) angle in radians. */
	float m_aspectRatio = 1.0f; /**< The aspect ratio of the camera's view (width divided by height). */
	float m_nearPlane = 0.01f; /**< The distance to the near clipping plane. */
	float m_farPlane = 1000.0f; /**< The distance to the far clipping plane. */

	bool m_viewDirty = true; /**< Flag indicating whether the view matrix needs to be recalculated. */
};