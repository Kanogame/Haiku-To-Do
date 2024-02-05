#include "MainWindow.h"
#include <iostream>

namespace ToDo {
	enum {
		M_BUTTON_ENTER = 'btn'
	};

	MainWindow::MainWindow(int width, int height) : BWindow(BRect(100,100,100 + width,100 + height),"Main Window",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS) {
		ConstructLayout(height, width, 5); 
	}

	void MainWindow::ConstructLayout(int windowH, int windowW, int padding) {	
		taskName = new BTextControl(BRect(padding, padding, windowW - padding, 30), "name", NULL, "put you input here", NULL, B_FOLLOW_LEFT | B_FOLLOW_RIGHT);
		AddChild(taskName);
		
		taskDesc = new BTextView(BRect(padding, 30 + padding, windowW - padding, 100), "desc" ,BRect(0, 0, 300, 100), NULL);
		taskDesc->SetText("put shit here");
		AddChild(taskDesc);
		
		BButton *button = new BButton(BRect(windowW - 100 - padding, 100 + padding, windowW - padding, 140), "button", "enter", new BMessage(M_BUTTON_ENTER), B_FOLLOW_RIGHT);
		AddChild(button);
		
		taskList = new BView(BRect(padding, 140 + padding, windowW - padding, windowH - padding), "list", B_FOLLOW_ALL_SIDES, 0);
		taskList->AdoptSystemColors();
		taskList->Show();
		AddChild(taskList);
	}

	void MainWindow::AddNewEntry(const char* name, const char* desc) {
		Items.push_back({name, desc, false});
		BView *task = new BView(BRect(0, nextOffset, 300, nextOffset + 50), "shti", 0, 0);
		task->AddChild(new BStringView(BRect(0, 0, 300, 20), "shit", name));
		task->AddChild(new BStringView(BRect(0, 20, 300, 55), "shit", desc));
		task->AdoptSystemColors();
		task->Show();
		taskList->AddChild(task);
		DisplayItems();
		nextOffset += 55;
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
