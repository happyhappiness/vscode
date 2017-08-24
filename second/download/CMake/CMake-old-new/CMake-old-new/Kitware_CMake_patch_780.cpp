@@ -9,6 +9,7 @@
 #include "cmCursesFilePathWidget.h"
 #include "cmCursesDummyWidget.h"
 #include "cmCursesCacheEntryComposite.h"
+#include "cmCursesLongMessageForm.h"
 
 const int cmCursesMainForm::MIN_WIDTH  = 65;
 const int cmCursesMainForm::MIN_HEIGHT = 6;
@@ -20,15 +21,16 @@ inline int ctrl(int z)
     return (z&037);
 } 
 
-cmCursesMainForm::cmCursesMainForm(const char* whereSource, 
-                                   const char* whereCMake,
-				   bool newCache) :
-  m_WhereSource(whereSource), m_WhereCMake(whereCMake)
+cmCursesMainForm::cmCursesMainForm(std::vector<std::string> const& args) :
+  m_Args(args)
 {
   m_Fields = 0;
-  m_Window = 0;
   m_Height = 0;
   m_Entries = 0;
+  m_AdvancedMode = false;
+  m_NumberOfVisibleEntries = 0;
+  m_OkToGenerate = false;
+  m_HelpMessage.push_back(s_ConstHelpMessage);
 }
 
 cmCursesMainForm::~cmCursesMainForm()
@@ -72,9 +74,8 @@ bool cmCursesMainForm::LookForCacheEntry(const char* key)
   return false;
 }
 
-void cmCursesMainForm::InitializeUI(WINDOW* w)
+void cmCursesMainForm::InitializeUI()
 {
-  m_Window = w;
 
   // Get the cache entries.
   const cmCacheManager::CacheEntryMap &cache = 
@@ -126,6 +127,7 @@ void cmCursesMainForm::InitializeUI(WINDOW* w)
 	{
 	newEntries->push_back(new cmCursesCacheEntryComposite(key, value,
 							      true));
+	m_OkToGenerate = false;
 	}
       }
 
@@ -160,6 +162,12 @@ void cmCursesMainForm::InitializeUI(WINDOW* w)
   delete m_Entries;
   m_Entries = newEntries;
   
+  this->RePost();
+}
+
+
+void cmCursesMainForm::RePost()
+{
   // Create the fields to be passed to the form.
   if (m_Form)
     {
@@ -168,16 +176,45 @@ void cmCursesMainForm::InitializeUI(WINDOW* w)
     m_Form = 0;
     }
   delete[] m_Fields;
-  int size = m_Entries->size();
-  m_Fields = new FIELD*[3*size+1];
-  for(int j=0; j < size; j++)
+
+  if (m_AdvancedMode)
+    {
+    m_NumberOfVisibleEntries = m_Entries->size();
+    }
+  else
+    {
+    m_NumberOfVisibleEntries = 0;
+    std::vector<cmCursesCacheEntryComposite*>::iterator it;
+    for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+      {
+      if (!m_AdvancedMode && cmCacheManager::GetInstance()->IsAdvanced(
+	(*it)->GetValue()))
+	{
+	continue;
+	}
+      m_NumberOfVisibleEntries++;
+      }
+    }
+
+  m_Fields = new FIELD*[3*m_NumberOfVisibleEntries+1];
+
+  int j=0;
+  std::vector<cmCursesCacheEntryComposite*>::iterator it;
+  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
     {
-    m_Fields[3*j]    = (*m_Entries)[j]->m_Label->m_Field;
-    m_Fields[3*j+1]  = (*m_Entries)[j]->m_IsNewLabel->m_Field;
-    m_Fields[3*j+2]  = (*m_Entries)[j]->m_Entry->m_Field;
+    if (!m_AdvancedMode && cmCacheManager::GetInstance()->IsAdvanced(
+      (*it)->GetValue()))
+      {
+      continue;
+      }
+    m_Fields[3*j]    = (*it)->m_Label->m_Field;
+    m_Fields[3*j+1]  = (*it)->m_IsNewLabel->m_Field;
+    m_Fields[3*j+2]  = (*it)->m_Entry->m_Field;
+    j++;
     }
+
   // Has to be null terminated.
-  m_Fields[3*size] = 0;
+  m_Fields[3*m_NumberOfVisibleEntries] = 0;
 }
 
 void cmCursesMainForm::Render(int left, int top, int width, int height)
@@ -205,41 +242,82 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
     return;
     }
 
-  height -= 5;
+  height -= 6;
   m_Height = height;
 
-  int size = m_Entries->size();
+  if (m_AdvancedMode)
+    {
+    m_NumberOfVisibleEntries = m_Entries->size();
+    }
+  else
+    {
+    m_NumberOfVisibleEntries = 0;
+    std::vector<cmCursesCacheEntryComposite*>::iterator it;
+    for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+      {
+      if (!m_AdvancedMode && cmCacheManager::GetInstance()->IsAdvanced(
+	(*it)->GetValue()))
+	{
+	continue;
+	}
+      m_NumberOfVisibleEntries++;
+      }
+    }
+
   bool isNewPage;
-  for(int i=0; i < size; i++)
+  int i=0;
+  std::vector<cmCursesCacheEntryComposite*>::iterator it;
+  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
     {
+    if (!m_AdvancedMode && cmCacheManager::GetInstance()->IsAdvanced(
+      (*it)->GetValue()))
+      {
+      continue;
+      }
     int row = (i % height) + 1;  
     int page = (i / height) + 1;
     isNewPage = ( page > 1 ) && ( row == 1 );
 
-    (*m_Entries)[i]->m_Label->Move(left, top+row-1, isNewPage);
-    (*m_Entries)[i]->m_IsNewLabel->Move(left+32, top+row-1, false);
-    (*m_Entries)[i]->m_Entry->Move(left+33, top+row-1, false);
+    (*it)->m_Label->Move(left, top+row-1, isNewPage);
+    (*it)->m_IsNewLabel->Move(left+32, top+row-1, false);
+    (*it)->m_Entry->Move(left+33, top+row-1, false);
+    i++;
     }
+
   m_Form = new_form(m_Fields);
   post_form(m_Form);
   this->UpdateStatusBar();
   this->PrintKeys();
-  touchwin(m_Window); 
+  touchwin(stdscr); 
   refresh();
 }
 
 void cmCursesMainForm::PrintKeys()
 {
   int x,y;
-  getmaxyx(m_Window, y, x);
+  getmaxyx(stdscr, y, x);
   if ( x < cmCursesMainForm::MIN_WIDTH  || 
        y < cmCursesMainForm::MIN_HEIGHT )
     {
     return;
     }
   char firstLine[512], secondLine[512];
-  sprintf(firstLine,  "C)onfigure             G)enerate and Exit");
-  sprintf(secondLine, "Q)uit                  H)elp");
+  if (m_OkToGenerate)
+    {
+    sprintf(firstLine,  "C)onfigure                 G)enerate and Exit            H)elp");
+    }
+  else
+    {
+    sprintf(firstLine,  "C)onfigure                                               H)elp");
+    }
+  if (m_AdvancedMode)
+    {
+    sprintf(secondLine, "Q)uit Without Generating   T)oggle Advanced Mode (On)");
+    }
+  else
+    {
+    sprintf(secondLine, "Q)uit Without Generating   T)oggle Advanced Mode (Off)");
+    }
 
   curses_move(y-2,0);
   printw(firstLine);
@@ -254,75 +332,118 @@ void cmCursesMainForm::PrintKeys()
 void cmCursesMainForm::UpdateStatusBar()
 {
   int x,y;
-  getmaxyx(m_Window, y, x);
+  getmaxyx(stdscr, y, x);
   if ( x < cmCursesMainForm::MIN_WIDTH  || 
        y < cmCursesMainForm::MIN_HEIGHT )
     {
+    clear();
     curses_move(0,0);
     printw("Window is too small. A size of at least %dx%d is required.",
 	   cmCursesMainForm::MIN_WIDTH, cmCursesMainForm::MIN_HEIGHT);
-    touchwin(m_Window); 
-    wrefresh(m_Window); 
+    touchwin(stdscr); 
+    wrefresh(stdscr); 
     return;
     }
 
   FIELD* cur = current_field(m_Form);
   int index = field_index(cur);
-  char* curField = field_buffer(m_Fields[index-2], 0);
+  cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
+    m_Fields[index-2]));
+  const char* curField = lbl->GetValue();
+
+  // We want to display this on the right
+  char help[128];
+  const char* helpString;
+  cmCacheManager::CacheEntry *entry = 
+    cmCacheManager::GetInstance()->GetCacheEntry(curField);
+  if (entry)
+    {
+    helpString = entry->m_HelpString.c_str();
+    if (strlen(helpString) > 127)
+      {
+      sprintf(help,"%127s", helpString);
+      }
+    else
+      {
+      sprintf(help,"%s", helpString);
+      }
+    }
+  else
+    {
+    sprintf(help," ");
+    }
 
-  char version[128];
-  sprintf(version,"(CMake Version %d.%d)", cmMakefile::GetMajorVersion(),
-	  cmMakefile::GetMinorVersion());
 
   char bar[cmCursesMainForm::MAX_WIDTH];
   int i, curFieldLen = strlen(curField);
-  int versionLen = strlen(version);
-  int leftLen = cmCursesMainForm::IDEAL_WIDTH - versionLen;
-  if (curFieldLen >= leftLen)
+  int helpLen = strlen(help);
+
+  int width;
+  if (x < cmCursesMainForm::MAX_WIDTH )
     {
-    strncpy(bar, curField, leftLen);
+    width = x;
     }
   else
     {
-    strcpy(bar, curField);
-    for(i=curFieldLen; i < leftLen; ++i) { bar[i] = ' '; }
+    width = cmCursesMainForm::MAX_WIDTH;
     }
-  strcpy(bar+leftLen, version);
 
-  if ( x < cmCursesMainForm::MAX_WIDTH )
+  int leftLen = width - helpLen;
+  if (curFieldLen >= width)
     {
-    if (x > cmCursesMainForm::IDEAL_WIDTH )
-      {
-      for(i=cmCursesMainForm::IDEAL_WIDTH; i < x; i++)
-	{
-	bar[i] = ' ';
-	}
-      }
-    bar[x] = '\0';
+    strncpy(bar, curField, width);
     }
   else
     {
-    for(i=cmCursesMainForm::IDEAL_WIDTH; 
-	i < cmCursesMainForm::MAX_WIDTH-1; i++)
+    strcpy(bar, curField);
+    bar[curFieldLen] = ':';
+    bar[curFieldLen+1] = ' ';
+    if (curFieldLen + helpLen + 2 >= width)
       {
-      bar[i] = ' ';
+      strncpy(bar+curFieldLen+2, help, width
+	- curFieldLen - 2);
+      }
+    else
+      {
+      strcpy(bar+curFieldLen+2, help);
+      for(i=curFieldLen+helpLen+2; i < width; ++i) 
+	{ 
+	bar[i] = ' '; 
+	}
       }
-    bar[cmCursesMainForm::MAX_WIDTH-1] = '\0';
     }
 
-  curses_move(y-3,0);
+  bar[width] = '\0';
+
+  char version[cmCursesMainForm::MAX_WIDTH];
+  char vertmp[128];
+  sprintf(vertmp,"CMake Version %d.%d", cmMakefile::GetMajorVersion(),
+	  cmMakefile::GetMinorVersion());
+  int sideSpace = (width-strlen(vertmp));
+  for(i=0; i<sideSpace; i++) { version[i] = ' '; }
+  sprintf(version+sideSpace, "%s", vertmp);
+  version[width] = '\0';
+
+  curses_move(y-4,0);
   attron(A_STANDOUT);
   printw(bar);
   attroff(A_STANDOUT);  
+  curses_move(y-3,0);
+  printw(version);
   pos_form_cursor(m_Form);
 }
 
 void cmCursesMainForm::RunCMake(bool generateMakefiles)
 {
 
   int x,y;
-  getmaxyx(m_Window, y, x);
-  
+  getmaxyx(stdscr, y, x);
+
+  clear();
+  curses_move(1,1);
+  printw("Running CMake, please wait.");
+  touchwin(stdscr);
+  refresh();
   endwin();
   // always save the current gui values to disk
   this->FillCacheManagerFromUI();
@@ -331,32 +452,66 @@ void cmCursesMainForm::RunCMake(bool generateMakefiles)
   // create a cmake object
   cmake make;
   // create the arguments for the cmake object
-  std::vector<std::string> args;
-  args.push_back(m_WhereCMake);
-  if (m_WhereSource != "")
-    {
-    std::string arg;
-    arg = m_WhereSource;
-    args.push_back(arg);
-    }
+  std::string whereCMake = cmSystemTools::GetProgramPath(m_Args[0].c_str());
+  whereCMake += "/cmake";
+
+  m_Args[0] = whereCMake;
+
+  // Get rid of previous errors
+  m_Errors = std::vector<std::string>();
+
   // run the generate process
-  if(make.Generate(args, generateMakefiles) != 0)
+  m_OkToGenerate = true;
+  if(make.Generate(m_Args, generateMakefiles) != 0 || !m_Errors.empty())
     {
-    // TODO : error message here
+    m_OkToGenerate = false;
     cmSystemTools::ResetErrorOccuredFlag();
+    int x,y;
+    getmaxyx(stdscr, y, x);
+    cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
+								"Errors which during last pass.");
+    CurrentForm = msgs;
+    msgs->Render(1,1,x,y);
+    msgs->HandleInput();
+    CurrentForm = this;
+    this->Render(1,1,x,y);
     }
 
-  m_Window = initscr(); /* Initialization */ 
+  initscr(); /* Initialization */ 
   noecho(); /* Echo off */ 
   cbreak(); /* nl- or cr not needed */ 
-  keypad(m_Window,TRUE); /* Use key symbols as 
+  keypad(stdscr,TRUE); /* Use key symbols as 
 			  KEY_DOWN*/ 
    
-  this->InitializeUI(m_Window);
+  this->InitializeUI();
   this->Render(1, 1, x, y);
   
 }
 
+void cmCursesMainForm::AddError(const char* message, const char* title)
+{
+  m_Errors.push_back(message);
+}
+
+void cmCursesMainForm::RemoveEntry(const char* value)
+{
+  if (!value)
+    {
+    return;
+    }
+
+  std::vector<cmCursesCacheEntryComposite*>::iterator it;
+  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+    {
+    const char* val = (*it)->GetValue();
+    if (  val && !strcmp(value, val) )
+      {
+      m_Entries->erase(it);
+      break;
+      }
+    }
+}
+
 // copy from the list box to the cache manager
 void cmCursesMainForm::FillCacheManagerFromUI()
 { 
@@ -397,23 +552,27 @@ void cmCursesMainForm::HandleInput()
     currentWidget = reinterpret_cast<cmCursesWidget*>(field_userptr(
       currentField));
 
-    if (!currentWidget || !currentWidget->HandleInput(key, m_Form, m_Window))
+    if (!currentWidget || !currentWidget->HandleInput(key, m_Form, stdscr))
       {
       // quit
       if ( key == 'q' )
 	{
 	break;
 	}
       // if not end of page, next field otherwise next page
+      // each entry consists of fields: label, isnew, value
+      // therefore, the label field for the prev. entry is index-5
+      // and the label field for the next entry is index+1
+      // (index always corresponds to the value field)
       else if ( key == KEY_DOWN || key == ctrl('n') )
 	{
 	FIELD* cur = current_field(m_Form);
 	unsigned int index = field_index(cur);
-	if ( index == 3*m_Entries->size()-1 )
+	if ( index == 3*m_NumberOfVisibleEntries-1 )
 	  {
 	  continue;
 	  }
-	if ( (index < 3*m_Entries->size()-1) && new_page(m_Fields[index+1]))
+	if (new_page(m_Fields[index+1]))
 	  {
 	  form_driver(m_Form, REQ_NEXT_PAGE);
 	  }
@@ -423,6 +582,10 @@ void cmCursesMainForm::HandleInput()
 	  }
 	}
       // if not beginning of page, previous field, otherwise previous page
+      // each entry consists of fields: label, isnew, value
+      // therefore, the label field for the prev. entry is index-5
+      // and the label field for the next entry is index+1
+      // (index always corresponds to the value field)
       else if ( key == KEY_UP || key == ctrl('p') )
 	{
 	FIELD* cur = current_field(m_Form);
@@ -456,11 +619,56 @@ void cmCursesMainForm::HandleInput()
 	{
 	this->RunCMake(false);
 	}
+      // display help
+      else if ( key == 'h' )
+	{
+	int x,y;
+	getmaxyx(stdscr, y, x);
+	cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_HelpMessage,
+								    "Help.");
+	CurrentForm = msgs;
+	msgs->Render(1,1,x,y);
+	msgs->HandleInput();
+	CurrentForm = this;
+	this->Render(1,1,x,y);
+	}
+      // display last errors
+      else if ( key == 'l' )
+	{
+	int x,y;
+	getmaxyx(stdscr, y, x);
+	cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
+								    "Errors which during last pass.");
+	CurrentForm = msgs;
+	msgs->Render(1,1,x,y);
+	msgs->HandleInput();
+	CurrentForm = this;
+	this->Render(1,1,x,y);
+	}
+      // switch advanced on/off
+      else if ( key == 't' )
+	{
+	if (m_AdvancedMode)
+	  {
+	  m_AdvancedMode = false;
+	  }
+	else
+	  {
+	  m_AdvancedMode = true;
+	  }
+	int x,y;
+	getmaxyx(stdscr, y, x);
+	this->RePost();
+	this->Render(1, 1, x, y);
+	}
       // generate and exit
       else if ( key == 'g' )
 	{
-	this->RunCMake(true);
-	break;
+	if ( m_OkToGenerate )
+	  {
+	  this->RunCMake(true);
+	  break;
+	  }
 	}
       // delete cache entry
       else if ( key == 'd' )
@@ -469,11 +677,16 @@ void cmCursesMainForm::HandleInput()
 	unsigned int index = field_index(cur);
 
 	// make the next or prev. current field after deletion
+	// each entry consists of fields: label, isnew, value
+	// therefore, the label field for the prev. entry is index-5
+	// and the label field for the next entry is index+1
+	// (index always corresponds to the value field)
 	FIELD* nextCur;
 	if ( index == 2 )
 	  {
+	  nextCur=0;
 	  }
-	else if ( index == 3*m_Entries->size()-1 )
+	else if ( index == 3*m_NumberOfVisibleEntries-1 )
 	  {
 	  nextCur = m_Fields[index-5];
 	  }
@@ -483,36 +696,49 @@ void cmCursesMainForm::HandleInput()
 	  }
 
 	// Get the label widget
+	// each entry consists of fields: label, isnew, value
+	// therefore, the label field for the is index-2
+	// (index always corresponds to the value field)
 	cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
 	  m_Fields[index-2]));
 	cmCacheManager::GetInstance()->RemoveCacheEntry(lbl->GetValue());
 
-	std::string nextVal (reinterpret_cast<cmCursesWidget*>(field_userptr(nextCur))->GetValue());
+	std::string nextVal;
+	if (nextCur)
+	  {
+	  nextVal = (reinterpret_cast<cmCursesWidget*>(field_userptr(nextCur))->GetValue());
+	  }
 
 	int x,y;
-	getmaxyx(m_Window, y, x);
-	this->InitializeUI(m_Window);
+	getmaxyx(stdscr, y, x);
+	this->RemoveEntry(lbl->GetValue());
+	this->RePost();
 	this->Render(1, 1, x, y);
 
-	// make the next or prev. current field after deletion
-	nextCur = 0;
-	std::vector<cmCursesCacheEntryComposite*>::iterator it;
-	for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+	if (nextCur)
 	  {
-	  if (nextVal == (*it)->m_Key)
+	  // make the next or prev. current field after deletion
+	  nextCur = 0;
+	  std::vector<cmCursesCacheEntryComposite*>::iterator it;
+	  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
 	    {
-	    nextCur = (*it)->m_Entry->m_Field;
+	    if (nextVal == (*it)->m_Key)
+	      {
+	      nextCur = (*it)->m_Entry->m_Field;
+	      }
+	    }
+	  
+	  if (nextCur)
+	    {
+	    set_current_field(m_Form, nextCur);
 	    }
-	  }
-
-	if (nextCur)
-	  {
-	  set_current_field(m_Form, nextCur);
 	  }
 	}
       }
 
-    touchwin(m_Window); 
-    wrefresh(m_Window); 
+    touchwin(stdscr); 
+    wrefresh(stdscr); 
     }
 }
+
+const char* cmCursesMainForm::s_ConstHelpMessage = "CMake is used to configure and generate build files for software projects.   The basic steps for configuring a project are as follows:\n\n1. Select the source directory for the project.  This should contain the CMakeLists.txt files for the project.\n\n2. Select the build directory for the project.   This is the directory where the project will be built.  It can be the same or a different directory than the source directory.   For easy clean up, a separate build directory is recommended.  CMake will create the directory if it does not exist.\n\n3. Once the source and binary directories are selected, it is time to press the Configure button.  This will cause CMake to read all of the input files and discover all the variables used by the project.   The first time a variable is displayed it will be in Red.   Users should inspect red variables making sure the values are correct.   For some projects the Configure process can be iterative, so continue to press the Configure button until there are no longer red entries.\n\n4. Once there are no longer red entries, you should click the OK button.  This will write the build files to the build directory and exit CMake.";