#include "MainWindow.h"
#include <iostream>
#include <stdio.h>
#include <sstream>

namespace ToDo {
	enum {
		M_BUTTON_ENTER = 'btn',
		M_CHECK_CHANGE = 'ch',
		M_SHOW_OPEN_FILE = 'sof',
		M_SHOW_SAVE_FILE = 'ssf',
		M_OPEN_FILE = 'of',
		M_SAVE_FILE = 'sf'
	};

	MainWindow::MainWindow(int width, int height) : BWindow(BRect(100,100,100 + width,100 + height),"Main Window",B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS) {
		ConstructLayout(height, width, 5);
		SetBar();
		BMessenger msgr(NULL, this);
		openFile = new BFilePanel(B_OPEN_PANEL, &msgr, NULL, 0, false, new BMessage(M_OPEN_FILE));
		saveFile = new BFilePanel(B_SAVE_PANEL, &msgr, NULL, 0, false, new BMessage(M_SAVE_FILE));	
	}

	void MainWindow::SetBar() {
		BMenuBar *bar = new BMenuBar(BRect(), "123");
		SetKeyMenuBar(bar);
	       	BMenu *fileDialog = new BMenu("File");	
		fileDialog->AddItem(new BMenuItem("Open", new BMessage(M_SHOW_OPEN_FILE)));	
		fileDialog->AddItem(new BMenuItem("Save", new BMessage(M_SHOW_SAVE_FILE)));	
		bar->AddItem(fileDialog);	
		bar->AddItem(new BMenuItem("About", NULL));	
		bar->Show();
		AddChild(bar);
	}

	void MainWindow::WriteFile(const char* path) {
		BFile file(path, B_WRITE_ONLY);
		std::cout << path << "\n";
		if (file.InitCheck() != B_OK) {
			std::cout << "bad path\n";
		}	
		for (int i = 0; i < Items.size(); i++) {
			std::stringstream ss;
			ss << Items[i].name << "|" <<  Items[i].desc << "|" << Items[i].isChecked << "\n";
			std::string data = ss.str();
			file.Write(data.c_str(), data.size());
		}
	}

	void MainWindow::ReadFile(const entry_ref &ref) {
		BFile file(&ref, B_READ_ONLY);
		if (file.InitCheck() != B_OK) {
			std::cout << "bad path\n";	
		}
		off_t fileSize = 0;
		file.GetSize(&fileSize);
		BString fileData;
		char *buffer = fileData.LockBuffer(fileSize + 10);
		file.Read(buffer, fileSize);
		fileData.UnlockBuffer();
		auto lines = SplitString(std::string("\n"), std::string(buffer));
		for (int i = 0; i < lines.size(); i++) {	
			auto res = SplitString(std::string("|"), lines[i]);
			for (int i = 0; i < res.size(); i++) {
				std::cout << res[i] <<  " | ";
			}
			std::cout <<  "\n";
		}

	}

	std::vector<std::string> MainWindow::SplitString(std::string delimiter, std::string haystack) {
		std::vector<std::string> res = {};	
		size_t next = 0;
		size_t prev = 0;
		while ((next = haystack.find(delimiter, prev)) != std::string::npos) {
			res.push_back(haystack.substr(prev, next-prev));
			prev = next + 1;
		}	
		res.push_back(haystack.substr(prev));
		return res;
	}

	void MainWindow::ConstructLayout(int windowH, int windowW, int padding) {
		int offset = 20;	
		taskName = new BTextControl(BRect(padding, offset + padding, windowW - padding, offset + 30), "name", NULL, "put you input here", NULL, B_FOLLOW_LEFT_RIGHT);
		AddChild(taskName);
		offset += 30;
		taskDesc = new BTextView(BRect(padding, offset + padding, windowW - padding, offset + 70), "desc" ,BRect(0, 0, 300, 100), B_FOLLOW_LEFT_RIGHT, B_FULL_UPDATE_ON_RESIZE|B_WILL_DRAW|B_PULSE_NEEDED);
		taskDesc->SetText("put shit here");
		AddChild(taskDesc);
		offset += 70;
		BButton *button = new BButton(BRect(windowW - 100 - padding, offset + padding, windowW - padding, offset + 40), "button", "enter", new BMessage(M_BUTTON_ENTER), B_FOLLOW_RIGHT);
		AddChild(button);
		offset += 40;
		
		taskList = new BView(BRect(padding, offset + padding, windowW - padding, windowH - padding), "list", B_FOLLOW_ALL_SIDES, 0);
		taskList->AdoptSystemColors();
		taskList->Show();
		AddChild(taskList);
	}

	void MainWindow::BuildItem(BView* taskList, const char* name, const char* desc, int id) {
		BView *task = new BView(BRect(0, nextOffset, 300, nextOffset + 50), "itemView", 0, 0);
		BMessage *msg = new BMessage(M_CHECK_CHANGE);
		msg->SetInt32("value", id);
		task->AddChild(new BCheckBox(BRect(0, 0, 20, 20), "itemCheckBox", "a", msg));
		task->AddChild(new BStringView(BRect(20, 0, 300, 20), "itemName", name));
		task->AddChild(new BStringView(BRect(20, 0, 300, 45), "itemDesc", desc));
		task->AdoptSystemColors();
		task->Show();
		taskList->AddChild(task);
	}

	void MainWindow::AddNewEntry(const char* name, const char* desc) {
		Items.push_back({name, desc, false});
		BuildItem(taskList, name, desc, Items.size() - 1);
		nextOffset += 55;
	}

	void MainWindow::DisplayItems() {
		for (int i = 0; i < Items.size(); i++) {
			std::cout << Items[i].name << " | " << Items[i].desc << " | " << Items[i].isChecked << "\n";
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
			case M_CHECK_CHANGE: {
				int value = msg->GetInt32("value", -1);
				if (value == -1) {
					break;
				}
				Items[value].isChecked = !Items[value].isChecked;
				break;
			}
			case M_SHOW_OPEN_FILE: {
				openFile->Show();
				break;
			} 
			case M_OPEN_FILE: {
				entry_ref ref;
				if (msg->FindRef("refs", &ref) != B_OK) {
					std::cout << "bad file\n";
				}
				ReadFile(ref);
				break;
			}
			case M_SHOW_SAVE_FILE: {
				saveFile->Show();
				break;
			} 
			case M_SAVE_FILE: {
				entry_ref dir;
				BString name;
				if (msg->FindRef("directory", &dir) == B_OK && msg->FindString("name", &name) == B_OK)
				{
					BPath path(&dir);
					path.Append(name);
					WriteFile(path.Path());
				}
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
