#include <Window.h>
#include <Application.h>
#include <TextControl.h>
#include <TextView.h>
#include <Button.h>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow : public BWindow
{
public:
						MainWindow(void);
			void		MessageReceived(BMessage *msg);
			bool		QuitRequested(void);
			
private:
			BTextControl *taskName;
			BTextView *taskDesc;
};

#endif
