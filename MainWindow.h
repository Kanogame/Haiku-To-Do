#include <Window.h>
#include <Application.h>
#include <TextControl.h>
#include <TextView.h>
#include <Button.h>
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
							MainWindow(void);
				void		MessageReceived(BMessage *msg);
				bool		QuitRequested(void);
				
		private:
				void		DisplayItems();
				void 		AddNewEntry(const char* name, const char* desc);
				std::vector<Item> Items;	
				BTextControl *taskName;
				BTextView *taskDesc;
	};
}
#endif
