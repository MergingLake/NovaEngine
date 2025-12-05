#pragma once
#include "Prerequisites.h"

/*
  @class Window
  @brief A class representing a window in the application.
*/
class 
Window {
public:
	/* 
		@brief Default constructor
	*/
	Window() = default;

	/* 
		@brief Destructor
	*/
	~Window() = default;

	/* 
		@brief Initializes the window.
		@details This method creates a window with the specified instance handle, command show parameter, and window procedure.
		@param hInstance The instance handle of the application.
		@param nCmdShow The command show parameter that specifies how the window is to be shown.
		@param wndProc The window procedure that processes messages sent to the window.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT 
	init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc);

	/* 
		@brief Updates the window.
		@details This method processes any necessary updates to the window state.
	*/
	void
	update();

	/* 
		@brief Renders the window.
		@details This method handles any rendering operations associated with the window.
	*/
	void
	render();

	/* 
		@brief Destroys the window and releases associated resources.
		@details This method cleans up and releases any resources allocated for the window.
	*/
	void
	destroy();

	HWND
		getHwnd() { return m_hWnd; }

public:
	HWND m_hWnd = nullptr;
	unsigned int m_width;
	unsigned int m_height;
private:
	HINSTANCE m_hInst = nullptr;
	RECT m_rect;
	std::string m_windowName = "Nova Engine";
};