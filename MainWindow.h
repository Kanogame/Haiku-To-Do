#include <iostream>
#include <sstream>
#include <string>
#include <vector> 

#include <Window.h>
#include <Application.h>
#include <TextControl.h>
#include <TextView.h>
#include <Button.h>
#include <ScrollBar.h>
#include <View.h>
#include <CheckBox.h>
#include <StringView.h>
#include <ScrollView.h>
#include <MenuItem.h>
#include <Menu.h>
#include <Path.h>
#include <MenuBar.h>

#include "Files.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

namespace ToDo {
	struct Item {
		const std::string name;
		const std::string desc;
		bool isChecked;
	};

	class MainWindow : public BWindow {
		public:
				MainWindow(int width, int height);
				void		MessageReceived(BMessage *msg);
				bool		QuitRequested(void);
				
		private:
				void		SetBar();
				void 		BuildItem(BView* taskList, const char* name, const char* desc, int id);
				void		ConstructLayout(int windowH, int windowW, int padding);
				void		DisplayItems();
				void 		AddNewEntry(const char* name, const char* desc);
				BFilePanel *openFile; 	
				BFilePanel *saveFile; 
				BView *taskList;
				std::vector<Item> Items;	
				BTextControl *taskName;
				BTextView *taskDesc;
				int nextOffset = 0;
	};
}
#endif
