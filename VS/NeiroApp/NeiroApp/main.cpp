#include "Output/Mouse.hpp"
#include "Output/Keyboard.hpp"
#include "GUI/GUI.hpp"
//#include "Input/Input.hpp"

int main(int argc, char *argv[])
{
	GUI_module::GUI gui(argc, argv);

	Output_module::Mouse mouse;
	Output_module::Keyboard keyboard;

	//Input_module::Input input;
	
	mouse.shiftCoords(100, 50, 1000);
	mouse.setCoords(0, 0, 1000);
  
	return gui.WaitingStopGUI();
}
