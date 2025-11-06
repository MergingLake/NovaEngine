#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/*
  @class SamplerState
  @brief A wrapper class for the ID3D11SamplerState interface.
	@note The SamplerState class is responsible for creating and managing Direct3D sampler state resources.
*/
class
  SamplerState {
public:
  /*
    @brief Constructor por defecto.
	*/
  SamplerState() = default;

  /*
		@brief Destructor.
  */
  ~SamplerState() = default;

  /*
		@brief Inicializa el Sampler State.
    @details Este método crea un Sampler State con configuración predeterminada
		(filtros lineales, wrap en coordenadas U,V,W).
    @param device Dispositivo donde se creará el Sampler State.
		@return HRESULT que indica éxito o fallo de la operación.
  */
  HRESULT
    init(Device& device);

  /*
		@brief Actualiza el Sampler State.
  */
  void
    update();

  /*
    @brief Renderiza el Sampler State.
    @details Este método enlaza el Sampler State al stage de pixel shader.
    @param deviceContext Contexto de dispositivo a utilizar para el renderizado.
    @param StartSlot Primer slot donde enlazar el Sampler State.
		@param NumSamplers Número de Sampler States a enlazar.
  */
  void
    render(DeviceContext& deviceContext,
      unsigned int StartSlot,
      unsigned int NumSamplers);

  /*
		@brief Destruye el Sampler State y libera los recursos asociados.
  */
  void
    destroy();

public:
  /*
		@brief Sampler State de D3D11 administrado por la clase.
  */
  ID3D11SamplerState* m_sampler = nullptr;
};