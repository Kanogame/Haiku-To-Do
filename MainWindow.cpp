#include "MainWindow.h"
#include <iostream>

namespace ToDo {
	enum {
		M_BUTTON_ENTER = 'btn'
	};

	MainWindow::MainWindow(void) : BWindow(BRect(100,100,500,400),"Main Window",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS) {
		taskName = new BTextControl(BRect(5, 5, 300, 30), "name", NULL, "put you input here", NULL, B_FOLLOW_LEFT | B_FOLLOW_RIGHT);
		AddChild(taskName);
		taskDesc = new BTextView(BRect(5, 40, 300, 100), "desc" ,BRect(0, 0, 300, 100), NULL);
		AddChild(taskDesc);
		taskDesc->SetText("put shit here");
		BButton *button = new BButton(BRect(5, 110, 100, 140), "button", "enter", new BMessage(M_BUTTON_ENTER));
		AddChild(button);
		taskList = new BView(BRect(5, 150, 300, 400), "list", 0, 0);
		taskList->AdoptSystemColors();
		taskList->Show();
		AddChild(taskList);
	}

	void MainWindow::AddNewEntry(const char* name, const char* desc) {
		Items.push_back({name, desc, false});
		//BView *task = new BView(BRect(0, nextOffset, 300, nextOffset + 20), "shti", 0, 0);
		taskList->AddChild(new BStringView(BRect(0, nextOffset, 300, nextOffset + 20), "shit", name));
		//task->AdoptSystemColors();
		//task->Show();
		//taskList->AddChild(task);
		DisplayItems();
		nextOffset += 25;
	}

	void MainWindow::DisplayItems() {
		for (int i = 0; i < Items.size(); i++) {
			std::cout << Items[i].name <<  "\n";
		} 
		std::cout  << "\n";
	}


	void MainWindow::MessageReceived(BMessage *msg) {
		switch (msg->what) {
			case M_BUTTON_ENTER: {
				SetTitle(taskName->Text());
				AddNewEntry(taskName->Text(), taskDesc->Text());
				break;
			}
			default: {
				BWindow::MessageReceived(msg);
				break;
			}
		}
	}


	bool MainWindow::QuitRequested(void) {
		be_app->PostMessage(B_QUIT_REQUESTED);
		return true;
	}
}
