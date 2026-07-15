#pragma once
#include <string>
#include <vector>

// Enumeración simple
enum class LogLevel { Message, Error };

// Interfaz para que tu GUI pueda escuchar
class ILogObserver {
public:
  virtual ~ILogObserver() = default;
  virtual void onLog(LogLevel level, const std::string& message) = 0;
};

/*
* @class Logger
* @brief Clase singleton para manejar el logging de mensajes y errores.
* Permite a los observadores suscribirse para recibir notificaciones de log.
*/
// Logger simple
class Logger {
public:
  /*
	* @brief Obtiene la instancia singleton del Logger.
	* @return Referencia a la instancia del Logger.
	* @note Esta función garantiza que solo exista una instancia de Logger en toda la aplicación.
  */
  static Logger& Get() { static Logger instance; return instance; }

  /*
	* @brief Suscribe un observador para recibir notificaciones de log.
	* @param observer Puntero al observador que implementa la interfaz ILogObserver.
	* @note Los observadores deben implementar el método onLog para manejar los mensajes de log.
	* @note Se recomienda que los observadores se desuscriban antes de ser destruidos para evitar referencias colgantes.
  */
  void Subscribe(ILogObserver* observer) { m_observers.push_back(observer); }

  /*
	* @brief Desuscribe un observador para dejar de recibir notificaciones de log.
	* @param observer Puntero al observador que se desea desuscribir.
	* @note Esta función elimina al observador de la lista de suscriptores, evitando que reciba futuros mensajes de log.
  */
  void LogRaw(const std::string& sender, const std::string& msg, LogLevel level) {
    std::string fullMsg = sender + " : " + msg;
    for (auto* obs : m_observers) obs->onLog(level, fullMsg);
  }

private:
  Logger() = default;
  std::vector<ILogObserver*> m_observers;
};