#include "MainWindow.h"

enum {
	M_BUTTON_ENTER = 'btn'
};

MainWindow::MainWindow(void) : BWindow(BRect(100,100,500,400),"Main Window",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS) {
	taskName = new BTextControl(BRect(5, 5, 300, 10), "box", "name", "put you input here", NULL, B_FOLLOW_LEFT | B_FOLLOW_RIGHT);
	AddChild(taskName);
	BButton *button = new BButton(BRect(5, 500, 100, 20), "button", "enter", new BMessage(M_BUTTON_ENTER));
	AddChild(button);
}


void
MainWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{
		case M_BUTTON_ENTER: {
			SetTitle(taskName->Text());
			break;
		}
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}
}


bool
MainWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
