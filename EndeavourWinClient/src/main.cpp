#include "core/window.h"

int main() {	
	if (!Window::CanInitialize()) {
		return -1;
	}

	Window::GenerateWindow(1366, 768, "EndeavourWinClient");

	if (Window::SetupOpenGL()) {

		Window::SetupCallbacks();

		Window::InitObjects();

		Window::Loop();
	}

	Window::CleanUp();
}