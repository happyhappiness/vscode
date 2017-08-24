@@ -10,6 +10,16 @@
 #include "cmCursesDummyWidget.h"
 #include "cmCursesCacheEntryComposite.h"
 
+const int cmCursesMainForm::MIN_WIDTH  = 65;
+const int cmCursesMainForm::MIN_HEIGHT = 6;
+const int cmCursesMainForm::IDEAL_WIDTH = 80;
+const int cmCursesMainForm::MAX_WIDTH = 512;
+
+inline int ctrl(int z)
+{
+    return (z&037);
+} 
+
 cmCursesMainForm::cmCursesMainForm(const char* whereSource, 
 				   bool newCache) :
   m_WhereSource(whereSource)
@@ -188,14 +198,13 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
     free_form(m_Form);
     m_Form = 0;
     }
-  if ( width < 22 || height < 2 )
+  if ( width < cmCursesMainForm::MIN_WIDTH  || 
+       height < cmCursesMainForm::MIN_HEIGHT )
     {
     return;
     }
 
-  std::cerr << "Rendering again." << std::endl;
-  
-  height -= 3;
+  height -= 5;
   m_Height = height;
 
   int size = m_Entries->size();
@@ -212,29 +221,98 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
     }
   m_Form = new_form(m_Fields);
   post_form(m_Form);
-  this->UpdateCurrentEntry();
+  this->UpdateStatusBar();
+  this->PrintKeys();
   touchwin(m_Window); 
   refresh();
 }
 
-void cmCursesMainForm::UpdateCurrentEntry()
+void cmCursesMainForm::PrintKeys()
 {
-  FIELD* cur = current_field(m_Form);
-  int index = field_index(cur);
-  char* text = field_buffer(m_Fields[index-2], 0);
-
   int x,y;
   getmaxyx(m_Window, y, x);
+  if ( x < cmCursesMainForm::MIN_WIDTH  || 
+       y < cmCursesMainForm::MIN_HEIGHT )
+    {
+    return;
+    }
+  char firstLine[512], secondLine[512];
+  sprintf(firstLine,  "C)onfigure             G)enerate and Exit");
+  sprintf(secondLine, "Q)uit                  H)elp");
+
+  move(y-2,0);
+  printw(firstLine);
   move(y-1,0);
-  printw(text);
+  printw(secondLine);
+  pos_form_cursor(m_Form);
+  
+}
+
+// Print the key of the current entry and the CMake version
+// on the status bar. Designed for a width of 80 chars.
+void cmCursesMainForm::UpdateStatusBar()
+{
+  int x,y;
+  getmaxyx(m_Window, y, x);
+  if ( x < cmCursesMainForm::MIN_WIDTH  || 
+       y < cmCursesMainForm::MIN_HEIGHT )
+    {
+    move(0,0);
+    printw("Window is too small. A size of at least %dx%d is required.",
+	   cmCursesMainForm::MIN_WIDTH, cmCursesMainForm::MIN_HEIGHT);
+    touchwin(m_Window); 
+    wrefresh(m_Window); 
+    return;
+    }
+
+  FIELD* cur = current_field(m_Form);
+  int index = field_index(cur);
+  char* curField = field_buffer(m_Fields[index-2], 0);
 
   char version[128];
-  sprintf(version,"CMake Version %d.%d", cmMakefile::GetMajorVersion(),
+  sprintf(version,"(CMake Version %d.%d)", cmMakefile::GetMajorVersion(),
 	  cmMakefile::GetMinorVersion());
-  int len = strlen(version);
-  move(y-1, x-len);
-  printw(version);
 
+  char bar[cmCursesMainForm::MAX_WIDTH];
+  int i, curFieldLen = strlen(curField);
+  int versionLen = strlen(version);
+  int leftLen = cmCursesMainForm::IDEAL_WIDTH - versionLen;
+  if (curFieldLen >= leftLen)
+    {
+    strncpy(bar, curField, leftLen);
+    }
+  else
+    {
+    strcpy(bar, curField);
+    for(i=curFieldLen; i < leftLen; ++i) { bar[i] = ' '; }
+    }
+  strcpy(bar+leftLen, version);
+
+  if ( x < cmCursesMainForm::MAX_WIDTH )
+    {
+    if (x > cmCursesMainForm::IDEAL_WIDTH )
+      {
+      for(i=cmCursesMainForm::IDEAL_WIDTH; i < x; i++)
+	{
+	bar[i] = ' ';
+	}
+      }
+    bar[x] = '\0';
+    }
+  else
+    {
+    for(i=cmCursesMainForm::IDEAL_WIDTH; 
+	i < cmCursesMainForm::MAX_WIDTH-1; i++)
+      {
+      bar[i] = ' ';
+      }
+    bar[cmCursesMainForm::MAX_WIDTH-1] = '\0';
+    }
+
+  move(y-3,0);
+  attron(A_STANDOUT);
+  printw(bar);
+  attroff(A_STANDOUT);  
   pos_form_cursor(m_Form);
 }
 
@@ -254,9 +332,12 @@ void cmCursesMainForm::RunCMake(bool generateMakefiles)
   // create the arguments for the cmake object
   std::vector<std::string> args;
   args.push_back("cmake");
-  std::string arg;
-  arg = m_WhereSource;
-  args.push_back(arg);
+  if (m_WhereSource != "")
+    {
+    std::string arg;
+    arg = m_WhereSource;
+    args.push_back(arg);
+    }
   // run the generate process
   if(make.Generate(args, generateMakefiles) != 0)
     {
@@ -269,7 +350,7 @@ void cmCursesMainForm::RunCMake(bool generateMakefiles)
   cbreak(); /* nl- or cr not needed */ 
   keypad(m_Window,TRUE); /* Use key symbols as 
 			  KEY_DOWN*/ 
-  
+   
   this->InitializeUI(m_Window);
   this->Render(1, 1, x, y);
   
@@ -307,7 +388,8 @@ void cmCursesMainForm::HandleInput()
   cmCursesWidget* currentWidget;
   while(1)
     {
-    this->UpdateCurrentEntry();
+    this->UpdateStatusBar();
+    this->PrintKeys();
     int key = getch();
 
     currentField = current_field(m_Form);
@@ -316,11 +398,13 @@ void cmCursesMainForm::HandleInput()
 
     if (!currentWidget || !currentWidget->HandleInput(key, m_Form, m_Window))
       {
+      // quit
       if ( key == 'q' )
 	{
 	break;
 	}
-      else if ( key == KEY_DOWN )
+      // if not end of page, next field otherwise next page
+      else if ( key == KEY_DOWN || key == ctrl('n') )
 	{
 	int x,y;
 	getmaxyx(m_Window, y, x);
@@ -339,7 +423,8 @@ void cmCursesMainForm::HandleInput()
 	  form_driver(m_Form, REQ_NEXT_FIELD);
 	  }
 	}
-      else if ( key == KEY_UP )
+      // if not beginning of page, previous field, otherwise previous page
+      else if ( key == KEY_UP || key == ctrl('p') )
 	{
 	int x,y;
 	getmaxyx(m_Window, y, x);
@@ -359,23 +444,75 @@ void cmCursesMainForm::HandleInput()
 	  form_driver(m_Form, REQ_PREV_FIELD);
 	  }
 	}
-      else if ( key == KEY_NPAGE )
+      // pg down
+      else if ( key == KEY_NPAGE || key == ctrl('d') )
 	{
 	form_driver(m_Form, REQ_NEXT_PAGE);
 	}
-      else if ( key == KEY_PPAGE )
+      // pg up
+      else if ( key == KEY_PPAGE || key == ctrl('u') )
 	{
 	form_driver(m_Form, REQ_PREV_PAGE);
 	}
+      // configure
       else if ( key == 'c' )
 	{
 	this->RunCMake(false);
 	}
-      else if ( key == 'o' )
+      // generate and exit
+      else if ( key == 'g' )
 	{
 	this->RunCMake(true);
 	break;
 	}
+      // delete cache entry
+      else if ( key == 'd' )
+	{
+	FIELD* cur = current_field(m_Form);
+	int index = field_index(cur);
+
+	// make the next or prev. current field after deletion
+	FIELD* nextCur;
+	if ( index == 2 )
+	  {
+	  }
+	else if ( index == 3*m_Entries->size()-1 )
+	  {
+	  nextCur = m_Fields[index-5];
+	  }
+	else
+	  {
+	  nextCur = m_Fields[index+1];
+	  }
+
+	// Get the label widget
+	cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
+	  m_Fields[index-2]));
+	cmCacheManager::GetInstance()->RemoveCacheEntry(lbl->GetValue());
+
+	std::string nextVal (reinterpret_cast<cmCursesWidget*>(field_userptr(nextCur))->GetValue());
+
+	int x,y;
+	getmaxyx(m_Window, y, x);
+	this->InitializeUI(m_Window);
+	this->Render(1, 1, x, y);
+
+	// make the next or prev. current field after deletion
+	nextCur = 0;
+	std::vector<cmCursesCacheEntryComposite*>::iterator it;
+	for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+	  {
+	  if (nextVal == (*it)->m_Key)
+	    {
+	    nextCur = (*it)->m_Entry->m_Field;
+	    }
+	  }
+
+	if (nextCur)
+	  {
+	  set_current_field(m_Form, nextCur);
+	  }
+	}
       }
 
     touchwin(m_Window); 