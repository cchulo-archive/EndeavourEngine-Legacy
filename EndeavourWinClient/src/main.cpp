#include "core/window.h"

int main() {	
	if (!Window::CanInitialize()) {
		return -1;
	}

	Window::GenerateWindow(1920, 1080, "EndeavourWinClient");

	if (Window::SetupOpenGL()) {

		Window::SetupCallbacks();

		Window::InitObjects();

		Window::Loop();
	}

	Window::CleanUp();
}