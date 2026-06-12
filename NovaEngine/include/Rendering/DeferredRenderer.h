#pragma once

#include "Buffer.h"
#include "DepthStencilState.h"
#include "DepthStencilView.h"
#include "RasterizerState.h"
#include "Rendering/ISceneRenderer.h"
#include "Rendering/RenderScene.h"
#include "Rendering/RenderTypes.h"
#include "SamplerState.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "EngineUtilities/Utilities/EditorViewportPass.h"

class Device;
class DeviceContext;
class Camera;
class Material;

/**
 * @class DeferredRenderer
 * @brief Implementa un pipeline diferido con GBuffer y lighting pass.
 *
 * El renderer usa deferred shading para superficies opacas y mantiene un subpass
 * forward para transparencias, de modo que el pipeline del editor siga funcionando
 * con el contenido actual del engine.
 */
class
	DeferredRenderer : public ISceneRenderer {
public:
	/*
	* @brief Inicializa el renderer diferido, creando recursos necesarios como buffers, texturas y shaders.
	* @param device Dispositivo con el cual se inicializan los recursos del renderer.
	* @return HRESULT indicando el éxito o fallo de la inicialización.
	*/
	HRESULT
		init(Device& device) override;

	/*
	* @brief Maneja el cambio de tamaño del viewport, recreando recursos dependientes del tamaño como render targets y depth stencils.
	* @param device Dispositivo con el cual se recrean los recursos.
	* @Param width Nuevo ancho del viewport.
	* @Param height Nuevo alto del viewport.
	* @return void
	*/
	void
		resize(Device& device, unsigned int width, unsigned int height) override;
	/*
	* @brief Renderiza la escena usando el pipeline diferido, incluyendo passes de geometría, iluminación y transparencias.
	* @param deviceContext Contexto del dispositivo para realizar las operaciones de renderizado.
	* @param camera Cámara que define la vista y proyección para el renderizado.
	* @param scene Escena que contiene los objetos a renderizar.
	* @param viewportPass Pass del editor que puede contener información adicional para el renderizado.
	* @return
	*/
	void
		render(DeviceContext& deviceContext,
			const Camera& camera,
			RenderScene& scene,
			EditorViewportPass& viewportPass) override;

	/*
	* @brief Libera todos los recursos asociados al renderer diferido, incluyendo buffers, texturas y shaders.
	* @return void
	*/
	void
		destroy() override;

	/*
	* @brief Obtiene el tipo de renderizado que implementa esta clase, en este caso RenderType::Deferred.
	* @return RenderType::Deferred
	*/
	ID3D11ShaderResourceView*
		getShadowMapSRV() const override { return m_shadowDepthSRV.m_textureFromImg; }

	/*
	* @brief Obtiene el Shader Resource View del mapa de sombras utilizado para depuración en el editor.
	* @return SRV del mapa de sombras para depuración.
	*/
	ID3D11ShaderResourceView*
		getPreShadowSRV() const override { return m_preShadowDebugPass.getSRV(); }

	/*
	* @brief Obtiene el Shader Resource View del GBuffer que contiene la información de albedo y metalicidad.
	* @return SRV del GBuffer de albedo y metalicidad.
	*/
	ID3D11ShaderResourceView*
		getGBufferAlbedoMetallicSRV() const override { return m_gBufferAlbedoMetallicSRV.m_textureFromImg; }

	/*
	* @brief Obtiene el Shader Resource View del GBuffer que contiene la información de normales y rugosidad.
	* @return SRV del GBuffer de normales y rugosidad.
	*/
	ID3D11ShaderResourceView*
		getGBufferNormalRoughnessSRV() const override { return m_gBufferNormalRoughnessSRV.m_textureFromImg; }

	/*
	* @brief Obtiene el Shader Resource View del GBuffer que contiene la información de oclusión ambiental en espacio mundial.
	* @return SRV del GBuffer de oclusión ambiental en espacio mundial.
	*/
	ID3D11ShaderResourceView*
		getGBufferWorldAoSRV() const override { return m_gBufferWorldAoSRV.m_textureFromImg; }

	/*
	* @brief Obtiene el Shader Resource View del GBuffer que contiene la información de emisividad y canal alfa.
	* @return SRV del GBuffer de emisividad y canal alfa.
	*/
	ID3D11ShaderResourceView*
		getGBufferEmissiveAlphaSRV() const override { return m_gBufferEmissiveAlphaSRV.m_textureFromImg; }

	/*
	* @brief Habilita o deshabilita la visualización de factores de sombra para depuración en el editor.
	* @param enabled Valor booleano que indica si la visualización de factores de sombra está habilitada o deshabilitada.
	* @return void
	*/
	void
		setShadowFactorDebugEnabled(bool enabled) override { m_shadowFactorDebugEnabled = enabled; }

	/*
	* @brief Establece el modo de visualización de depuración para el renderer diferido en el editor.
	* @param mode Entero que representa el modo de visualización de depuración a aplicar. Los valores específicos del modo deben ser definidos en la implementación del renderer y pueden incluir opciones como mostrar solo el GBuffer, visualizar las normales, etc.
	* @return void
	*/
	void
		setDeferredDebugViewMode(int mode) override { m_deferredDebugViewMode = mode; }

	/*
	* @brief Obtiene el nombre de depuración del renderer, que puede ser utilizado en el editor para identificar el tipo de renderer activo.
	* @return Cadena de caracteres que representa el nombre de depuración del renderer, en este caso "DeferredRenderer".
	*/
	const char*
		getDebugName() const override { return "DeferredRenderer"; }

private:
    #pragma once

    #include "Buffer.h"
    #include "DepthStencilState.h"
    #include "DepthStencilView.h"
    #include "RasterizerState.h"
    #include "Rendering/ISceneRenderer.h"
    #include "Rendering/RenderScene.h"
    #include "Rendering/RenderTypes.h"
    #include "SamplerState.h"
    #include "ShaderProgram.h"
    #include "Texture.h"
    #include "EngineUtilities/Utilities/EditorViewportPass.h"

    class Device;
    class DeviceContext;
    class Camera;
    class Material;

    /**
     * @class DeferredRenderer
     * @brief Implementa un pipeline diferido con GBuffer y lighting pass.
     *
     * El renderer usa deferred shading para superficies opacas y mantiene un subpass
     * forward para transparencias, de modo que el pipeline del editor siga funcionando
     * con el contenido actual del engine.
     */
    class
					DeferredRenderer : public ISceneRenderer {
    public:
					/*
					* @brief Inicializa el renderer diferido, creando recursos necesarios como buffers, texturas y shaders.
					* @param device Dispositivo con el cual se inicializan los recursos del renderer.
					* @return HRESULT indicando el éxito o fallo de la inicialización.
					*/
					HRESULT
						init(Device& device) override;

					/*
					* @brief Maneja el cambio de tamaño del viewport, recreando recursos dependientes del tamaño como render targets y depth stencils.
					* @param device Dispositivo con el cual se recrean los recursos.
					* @Param width Nuevo ancho del viewport.
					* @Param height Nuevo alto del viewport.
					* @return void
					*/
					void
						resize(Device& device, unsigned int width, unsigned int height) override;
					/*
					* @brief Renderiza la escena usando el pipeline diferido, incluyendo passes de geometría, iluminación y transparencias.
					* @param deviceContext Contexto del dispositivo para realizar las operaciones de renderizado.
					* @param camera Cámara que define la vista y proyección para el renderizado.
					* @param scene Escena que contiene los objetos a renderizar.
					* @param viewportPass Pass del editor que puede contener información adicional para el renderizado.
					* @return
					*/
					void
						render(DeviceContext& deviceContext,
							const Camera& camera,
							RenderScene& scene,
							EditorViewportPass& viewportPass) override;

					/*
					* @brief Libera todos los recursos asociados al renderer diferido, incluyendo buffers, texturas y shaders.
					* @return void
					*/
					void
						destroy() override;

					/*
					* @brief Obtiene el tipo de renderizado que implementa esta clase, en este caso RenderType::Deferred.
					* @return RenderType::Deferred
					*/
					ID3D11ShaderResourceView*
						getShadowMapSRV() const override { return m_shadowDepthSRV.m_textureFromImg; }

					/*
					* @brief Obtiene el Shader Resource View del mapa de sombras utilizado para depuración en el editor.
					* @return SRV del mapa de sombras para depuración.
					*/
					ID3D11ShaderResourceView*
						getPreShadowSRV() const override { return m_preShadowDebugPass.getSRV(); }

					/*
					* @brief Obtiene el Shader Resource View del GBuffer que contiene la información de albedo y metalicidad.
					* @return SRV del GBuffer de albedo y metalicidad.
					*/
					ID3D11ShaderResourceView*
						getGBufferAlbedoMetallicSRV() const override { return m_gBufferAlbedoMetallicSRV.m_textureFromImg; }

					/*
					* @brief Obtiene el Shader Resource View del GBuffer que contiene la información de normales y rugosidad.
					* @return SRV del GBuffer de normales y rugosidad.
					*/
					ID3D11ShaderResourceView*
						getGBufferNormalRoughnessSRV() const override { return m_gBufferNormalRoughnessSRV.m_textureFromImg; }

					/*
					* @brief Obtiene el Shader Resource View del GBuffer que contiene la información de oclusión ambiental en espacio mundial.
					* @return SRV del GBuffer de oclusión ambiental en espacio mundial.
					*/
					ID3D11ShaderResourceView*
						getGBufferWorldAoSRV() const override { return m_gBufferWorldAoSRV.m_textureFromImg; }

					/*
					* @brief Obtiene el Shader Resource View del GBuffer que contiene la información de emisividad y canal alfa.
					* @return SRV del GBuffer de emisividad y canal alfa.
					*/
					ID3D11ShaderResourceView*
						getGBufferEmissiveAlphaSRV() const override { return m_gBufferEmissiveAlphaSRV.m_textureFromImg; }

					/*
					* @brief Habilita o deshabilita la visualización de factores de sombra para depuración en el editor.
					* @param enabled Valor booleano que indica si la visualización de factores de sombra está habilitada o deshabilitada.
					* @return void
					*/
					void
						setShadowFactorDebugEnabled(bool enabled) override { m_shadowFactorDebugEnabled = enabled; }

					/*
					* @brief Establece el modo de visualización de depuración para el renderer diferido en el editor.
					* @param mode Entero que representa el modo de visualización de depuración a aplicar. Los valores específicos del modo deben ser definidos en la implementación del renderer y pueden incluir opciones como mostrar solo el GBuffer, visualizar las normales, etc.
					* @return void
					*/
					void
						setDeferredDebugViewMode(int mode) override { m_deferredDebugViewMode = mode; }

					/*
					* @brief Obtiene el nombre de depuración del renderer, que puede ser utilizado en el editor para identificar el tipo de renderer activo.
					* @return Cadena de caracteres que representa el nombre de depuración del renderer, en este caso "DeferredRenderer".
					*/
					const char*
						getDebugName() const override { return "DeferredRenderer"; }

    private:
					/**
      * @brief Construye las colas de renderizado separando objetos opacos y transparentes.
      *
      * Recorre los objetos de la escena, aplica culling basado en la cámara y clasifica
      * los objetos en m_opaqueQueue y m_transparentQueue según sus propiedades/materiales.
      *
      * @param scene Escena que contiene los objetos a procesar.
      * @param camera Cámara usada para realizar pruebas de visibilidad (frustum culling).
      */
					void buildQueues(RenderScene& scene, const Camera& camera);

					/**
      * @brief Actualiza constantes por-frame y estados dependientes de la cámara/escena.
      *
      * Actualiza los buffers constantes (m_perFrameBuffer, m_lightingDebugBuffer, etc.)
      * con datos derivados de la cámara y de la escena, y sube esos datos al GPU mediante
      * DeviceContext::UpdateSubresource.
      *
      * @param camera Cámara actual usada para calcular matrices de vista/proyección.
      * @param scene Escena que puede aportar información de luces y parámetros globales.
      * @param deviceContext Contexto del dispositivo utilizado para las actualizaciones.
      */
					void updatePerFrame(const Camera& camera, const RenderScene& scene, DeviceContext& deviceContext);

					/**
      * @brief Calcula y actualiza las matrices de luz necesarias para el pase de sombras.
      *
      * Genera matrices de vista/proyección para cada luz que proyecta sombras, actualiza
      * estructuras internas que serán usadas por renderShadowPass() y por los shaders de iluminación.
      *
      * @param camera Cámara actual que puede influir en la selección y cascadas de sombras.
      * @param scene Escena cuyos datos de luz se utilizarán para construir las matrices.
      */
					void updateLightMatrices(const Camera& camera, const RenderScene& scene);

					/**
      * @brief Renderiza la escena hacia un target específico (por ejemplo, el viewport del editor).
      *
      * Ejecuta todo el flujo: generación de G-Buffer, pase de iluminación, skybox y objetos transparentes.
      * Puede opcionalmente aplicar sombras si applyShadows == true.
      *
      * @param deviceContext Contexto de renderizado.
      * @param scene Escena a renderizar.
      * @param targetPass EditorViewportPass destino donde se escribirá el color final.
      * @param applyShadows Si es true, se ejecutarán los pases de sombras y se tomarán en cuenta en iluminación.
      */
					void renderSceneToTarget(DeviceContext& deviceContext, RenderScene& scene, EditorViewportPass& targetPass, bool applyShadows);

					/**
      * @brief Enlaza los render targets del GBuffer y el depth stencil para el pase de geometría.
      *
      * Configura el OMSetRenderTargets con las vistas RTVs del GBuffer y el DSV provisto,
      * además de ajustar el viewport y limpiar los targets según sea necesario.
      *
      * @param deviceContext Contexto donde se realizará el bind.
      * @param depthStencilView Depth stencil view a usar (puede ser el principal de la escena).
      */
					void bindGBufferTargets(DeviceContext& deviceContext, ID3D11DepthStencilView* depthStencilView);

					/**
      * @brief Enlaza el render target final (por ejemplo el del EditorViewportPass) para compositing.
      *
      * Establece el RenderTargetView final y el DepthStencilView, ajusta estados y realiza
      * las limpiezas iniciales necesarias.
      *
      * @param deviceContext Contexto de renderizado.
      * @param renderTargetView Vista del render target final donde se escribirá el color compuesto.
      * @param depthStencilView Depth stencil view asociado (puede ser nullptr si no se requiere).
      */
					void bindFinalTarget(DeviceContext& deviceContext, ID3D11RenderTargetView* renderTargetView, ID3D11DepthStencilView* depthStencilView);

					/**
      * @brief Limpia las SRV vinculadas anteriormente usadas por los pasos diferidos.
      *
      * Desvincula (setea a null) las SRVs usadas por el pixel shader para evitar hazards
      * al escribir en los mismos recursos como render targets en pasos posteriores.
      *
      * @param deviceContext Contexto del dispositivo en el que se limpiarán los bindings.
      */
					void clearDeferredSRVs(DeviceContext& deviceContext);

					/**
      * @brief Ejecuta el pase de geometría que rellena el GBuffer.
      *
      * Recorre la cola de objetos opacos, configura el shader de GBuffer y dibuja cada objeto
      * llamando a renderGeometryObject(). No debe escribir en el render target final.
      *
      * @param deviceContext Contexto de renderizado.
      */
					void renderGeometryPass(DeviceContext& deviceContext);

					/**
      * @brief Renderiza un objeto en el pase de geometría hacia el GBuffer.
      *
      * Ajusta estados gráficos según el material del objeto, enlaza sus buffers y emite
      * la llamada DrawIndexed correspondiente.
      *
      * @param deviceContext Contexto de renderizado.
      * @param object Puntero al RenderObject a dibujar.
      */
					void renderGeometryObject(DeviceContext& deviceContext, const RenderObject& object);

					/**
      * @brief Ejecuta el pase de iluminación diferida que consume el GBuffer y produce la imagen final.
      *
      * Configura el shader de iluminación (m_deferredLightingShader), enlaza las SRVs del GBuffer,
      * establece samplers y realiza un draw fullscreen para componer la iluminación.
      *
      * @param deviceContext Contexto de renderizado.
      */
					void renderLightingPass(DeviceContext& deviceContext);

					/**
      * @brief Renderiza el skybox de la escena.
      *
      * Dibuja el skybox después del pase de iluminación o en el momento apropiado del pipeline,
      * usando el shader y recursos de skybox necesarios.
      *
      * @param deviceContext Contexto de renderizado.
      * @param scene Escena que puede contener la referencia al cubemap del skybox.
      */
					void renderSkyboxPass(DeviceContext& deviceContext, RenderScene& scene);

					/**
      * @brief Renderiza los objetos transparentes en un pase forward.
      *
      * Ordena (si procede) y dibuja los objetos transparentes desde la cola m_transparentQueue,
      * aplicando blending y depth states adecuados.
      *
      * @param deviceContext Contexto de renderizado.
      */
					void renderTransparentPass(DeviceContext& deviceContext);

					/**
      * @brief Renderiza un objeto usando el pipeline forward (para transparencias u otros passes).
      *
      * Se usa tanto para objetos transparentes como para otros sub-passes forward (por ejemplo, partículas).
      * Selecciona shaders, blend state y draw call según el RenderPassType.
      *
      * @param deviceContext Contexto de renderizado.
      * @param object Puntero al RenderObject a dibujar.
      * @param passType Tipo de pase forward (por ejemplo: Transparent, ForwardOpaque, etc.).
      */
					void renderForwardObject(DeviceContext& deviceContext, const RenderObject& object, RenderPassType passType);

					/**
      * @brief Ejecuta el pase de sombras, renderizando mapas de profundidad para luces relevantes.
      *
      * Configura el render target de profundidad (m_shadowDSV), usa m_shadowShader y renderiza
      * los objetos que castran sombras llamando a renderShadowObject().
      *
      * @param deviceContext Contexto de renderizado.
      */
					void renderShadowPass(DeviceContext& deviceContext);

					/**
      * @brief Renderiza un objeto dentro del pase de sombras (escribe únicamente profundidad).
      *
      * Configura el shader de sombras, las matrices por objeto y emite la draw call para
      * poblar el shadow map.
      *
      * @param deviceContext Contexto de renderizado.
      * @param object Puntero al RenderObject que proyectará sombras.
      */
					void renderShadowObject(DeviceContext& deviceContext, const RenderObject& object);

					/**
      * @brief Crea los recursos necesarios para la generación de mapas de sombras (texturas, DSV, shaders).
      *
      * Inicializa m_shadowDepthTexture, m_shadowDepthSRV, m_shadowDSV, m_shadowShader y m_shadowRasterizer.
      *
      * @param device Dispositivo usado para crear los recursos.
      * @return S_OK en caso de éxito, código HRESULT de error en caso contrario.
      */
					HRESULT createShadowResources(Device& device);

					/**
      * @brief Crea las texturas y render targets que componen el GBuffer para las dimensiones dadas.
      *
      * Inicializa los Textures y RTVs para albedo/metal, normal/roughness, world AO y emissive/alpha.
      *
      * @param device Dispositivo usado para crear recursos.
      * @param width Ancho del render target.
      * @param height Alto del render target.
      * @return S_OK en caso de éxito, código HRESULT en caso contrario.
      */
					HRESULT createGBufferResources(Device& device, unsigned int width, unsigned int height);

					/**
      * @brief Helper para crear un target del GBuffer con formato y bindings específicos.
      *
      * Crea una Texture de render target, su SRV asociada y un RenderTargetView configurado.
      *
      * @param device Dispositivo para la creación.
      * @param width Ancho de la textura.
      * @param height Alto de la textura.
      * @param format Formato DXGI de la textura.
      * @param texture Referencia donde se almacenará la textura creada.
      * @param srv Referencia donde se almacenará la SRV creada a partir de la textura.
      * @param rtv Referencia donde se almacenará el RenderTargetView asociado.
      * @return S_OK en caso de éxito, código HRESULT en caso contrario.
      */
					HRESULT createGBufferTarget(Device& device,
						unsigned int width,
						unsigned int height,
						DXGI_FORMAT format,
						Texture& texture,
						Texture& srv,
						RenderTargetView& rtv);

					/**
      * @brief Crea recursos para el pase de iluminación (shaders, samplers, quad full-screen).
      *
      * Inicializa m_deferredLightingShader, m_lightingSampler y otros recursos auxiliares.
      *
      * @param device Dispositivo para la creación de recursos.
      * @return S_OK en caso de éxito, código HRESULT en caso contrario.
      */
					HRESULT createLightingResources(Device& device);

					/**
      * @brief Crea el quad de pantalla completa usado para componer la iluminación y postprocesado.
      *
      * Crea y rellena m_fullscreenVertexBuffer y m_fullscreenIndexBuffer.
      *
      * @param device Dispositivo para la creación de buffers.
      * @return S_OK en caso de éxito, código HRESULT en caso contrario.
      */
					HRESULT createFullScreenQuad(Device& device);

					/**
      * @brief Crea los estados de blending utilizados por los materiales (alpha, opaque, additive, premultiplied).
      *
      * Inicializa m_alphaBlendState, m_opaqueBlendState, m_additiveBlendState y m_premultipliedBlendState.
      *
      * @param device Dispositivo para la creación de estados.
      * @return S_OK en caso de éxito, código HRESULT en caso contrario.
      */
					HRESULT createBlendStates(Device& device);

					/**
      * @brief Resuelve el estado de blending apropiado para un material dado.
      *
      * Revisa el blend mode del material y devuelve el ID3D11BlendState* correspondiete (puede ser nullptr).
      *
      * @param material Puntero al Material cuyo blend mode se debe resolver.
      * @return Puntero a ID3D11BlendState a aplicar; nullptr si se debe usar el estado por defecto.
      */
					ID3D11BlendState* resolveBlendState(const Material* material) const;

    private:
					Buffer m_perFrameBuffer;
					Buffer m_perObjectBuffer;
					Buffer m_perMaterialBuffer;
					Buffer m_lightingDebugBuffer;
					Buffer m_fullscreenVertexBuffer;
					Buffer m_fullscreenIndexBuffer;

					DepthStencilState m_transparentDepthStencil;
					DepthStencilState m_disabledDepthStencil;
					DepthStencilState m_shadowDepthStencil;

					ID3D11BlendState* m_alphaBlendState = nullptr;
					ID3D11BlendState* m_opaqueBlendState = nullptr;
					ID3D11BlendState* m_additiveBlendState = nullptr;
					ID3D11BlendState* m_premultipliedBlendState = nullptr;
					float m_blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

					Texture m_shadowDepthTexture;
					Texture m_shadowDepthSRV;
					DepthStencilView m_shadowDSV;
					ShaderProgram m_shadowShader;
					RasterizerState m_shadowRasterizer;
					unsigned int m_shadowMapSize = 2048;

					ShaderProgram m_gBufferShader;
					ShaderProgram m_deferredLightingShader;
					SamplerState m_lightingSampler;
					RasterizerState m_fullscreenRasterizer;

					Texture m_gBufferAlbedoMetallicTexture;
					Texture m_gBufferAlbedoMetallicSRV;
					RenderTargetView m_gBufferAlbedoMetallicRTV;

					Texture m_gBufferNormalRoughnessTexture;
					Texture m_gBufferNormalRoughnessSRV;
					RenderTargetView m_gBufferNormalRoughnessRTV;

					Texture m_gBufferWorldAoTexture;
					Texture m_gBufferWorldAoSRV;
					RenderTargetView m_gBufferWorldAoRTV;

					Texture m_gBufferEmissiveAlphaTexture;
					Texture m_gBufferEmissiveAlphaSRV;
					RenderTargetView m_gBufferEmissiveAlphaRTV;

					EditorViewportPass m_preShadowDebugPass;
					bool m_applyShadows = true;
					unsigned int m_renderWidth = 1280;
					unsigned int m_renderHeight = 720;

					CBPerFrame m_cbPerFrame{};
					CBPerObject m_cbPerObject{};
					CBPerMaterial m_cbPerMaterial{};
					struct DeferredLightingDebugData {
						int DebugViewMode = 0;
						float ShadowStrength = 1.0f;
						float pad0 = 0.0f;
						float pad1 = 0.0f;
					} m_lightingDebugData{};
					bool m_shadowFactorDebugEnabled = false;
					int m_deferredDebugViewMode = 0;

					std::vector<const RenderObject*> m_opaqueQueue;
					std::vector<const RenderObject*> m_transparentQueue;
    };

private:
	Buffer m_perFrameBuffer;
	Buffer m_perObjectBuffer;
	Buffer m_perMaterialBuffer;
	Buffer m_lightingDebugBuffer;
	Buffer m_fullscreenVertexBuffer;
	Buffer m_fullscreenIndexBuffer;

	DepthStencilState m_transparentDepthStencil;
	DepthStencilState m_disabledDepthStencil;
	DepthStencilState m_shadowDepthStencil;

	ID3D11BlendState* m_alphaBlendState = nullptr;
	ID3D11BlendState* m_opaqueBlendState = nullptr;
	ID3D11BlendState* m_additiveBlendState = nullptr;
	ID3D11BlendState* m_premultipliedBlendState = nullptr;
	float m_blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	Texture m_shadowDepthTexture;
	Texture m_shadowDepthSRV;
	DepthStencilView m_shadowDSV;
	ShaderProgram m_shadowShader;
	RasterizerState m_shadowRasterizer;
	unsigned int m_shadowMapSize = 2048;

	ShaderProgram m_gBufferShader;
	ShaderProgram m_deferredLightingShader;
	SamplerState m_lightingSampler;
	RasterizerState m_fullscreenRasterizer;

	Texture m_gBufferAlbedoMetallicTexture;
	Texture m_gBufferAlbedoMetallicSRV;
	RenderTargetView m_gBufferAlbedoMetallicRTV;

	Texture m_gBufferNormalRoughnessTexture;
	Texture m_gBufferNormalRoughnessSRV;
	RenderTargetView m_gBufferNormalRoughnessRTV;

	Texture m_gBufferWorldAoTexture;
	Texture m_gBufferWorldAoSRV;
	RenderTargetView m_gBufferWorldAoRTV;

	Texture m_gBufferEmissiveAlphaTexture;
	Texture m_gBufferEmissiveAlphaSRV;
	RenderTargetView m_gBufferEmissiveAlphaRTV;

	EditorViewportPass m_preShadowDebugPass;
	bool m_applyShadows = true;
	unsigned int m_renderWidth = 1280;
	unsigned int m_renderHeight = 720;

	CBPerFrame m_cbPerFrame{};
	CBPerObject m_cbPerObject{};
	CBPerMaterial m_cbPerMaterial{};
	struct DeferredLightingDebugData {
		int DebugViewMode = 0;
		float ShadowStrength = 1.0f;
		float pad0 = 0.0f;
		float pad1 = 0.0f;
	} m_lightingDebugData{};
	bool m_shadowFactorDebugEnabled = false;
	int m_deferredDebugViewMode = 0;

	std::vector<const RenderObject*> m_opaqueQueue;
	std::vector<const RenderObject*> m_transparentQueue;
};