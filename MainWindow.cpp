#include "MainWindow.h"

enum {
	M_BUTTON_ENTER = 'btn'
};

MainWindow::MainWindow(void) : BWindow(BRect(100,100,500,400),"Main Window",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS) {
	taskName = new BTextControl(BRect(5, 5, 300, 30), "name", NULL, "put you input here", NULL, B_FOLLOW_LEFT | B_FOLLOW_RIGHT);
	AddChild(taskName);
	taskDesc = new BTextView(BRect(5, 40, 300, 100), "desc" ,BRect(0, 0, 300, 100), NULL);
	AddChild(taskDesc);
	taskDesc->SetText("put shit here");
	BButton *button = new BButton(BRect(5, 200, 100, 20), "button", "enter", new BMessage(M_BUTTON_ENTER));
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
