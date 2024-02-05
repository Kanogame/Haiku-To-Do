#include <Window.h>
#include <Application.h>
#include <TextControl.h>
#include <TextView.h>
#include <Button.h>
#include <ScrollBar.h>
#include <View.h>
#include <CheckBox.h>
#include <StringView.h>

#include <vector> 
#include <string>

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
				void 		BuildItem(BView* taskList, const char* name, const char* desc, int id);
				void		ConstructLayout(int windowH, int windowW, int padding);
				void		DisplayItems();
				void 		AddNewEntry(const char* name, const char* desc);
				BView *taskList;
				std::vector<Item> Items;	
				BTextControl *taskName;
				BTextView *taskDesc;
				int nextOffset = 0;
	};
}
#endif
