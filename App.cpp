#include "App.h"
#include "MainWindow.h"


App::App(void)
	:	BApplication("application/x-vnd.dw-TestApp")
{
	ToDo::MainWindow *mainwin = new ToDo::MainWindow(300, 500);
	mainwin->Show();
}


int
main(void)
{
	App *app = new App();
	app->Run();
	delete app;
	return 0;
}
