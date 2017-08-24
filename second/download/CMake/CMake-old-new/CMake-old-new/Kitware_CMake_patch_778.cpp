@@ -20,8 +20,8 @@ inline int ctrl(int z)
 cmCursesMainForm::cmCursesMainForm(std::vector<std::string> const& args) :
   m_Args(args)
 {
+  m_NumberOfPages = 0;
   m_Fields = 0;
-  m_Height = 0;
   m_Entries = 0;
   m_AdvancedMode = false;
   m_NumberOfVisibleEntries = 0;
@@ -53,6 +53,7 @@ cmCursesMainForm::~cmCursesMainForm()
   delete m_Entries;
 }
 
+// See if a cache entry is in the list of entries in the ui.
 bool cmCursesMainForm::LookForCacheEntry(const char* key)
 {
   if (!key || !m_Entries)
@@ -72,13 +73,16 @@ bool cmCursesMainForm::LookForCacheEntry(const char* key)
   return false;
 }
 
+// Create new cmCursesCacheEntryComposite entries from the cache
 void cmCursesMainForm::InitializeUI()
 {
 
   // Get the cache entries.
   const cmCacheManager::CacheEntryMap &cache = 
     cmCacheManager::GetInstance()->GetCacheMap();
 
+  // Create a vector of cmCursesCacheEntryComposite's
+  // which contain labels, entries and new entry markers
   std::vector<cmCursesCacheEntryComposite*>* newEntries =
     new std::vector<cmCursesCacheEntryComposite*>;
   newEntries->reserve(cache.size());
@@ -149,8 +153,10 @@ void cmCursesMainForm::InitializeUI()
       }
     }
   
+  // Clean old entries
   if (m_Entries)
     {
+    // Have to call delete on each pointer
     std::vector<cmCursesCacheEntryComposite*>::iterator it;
     for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
       {
@@ -160,6 +166,7 @@ void cmCursesMainForm::InitializeUI()
   delete m_Entries;
   m_Entries = newEntries;
   
+  // Compute fields from composites
   this->RePost();
 }
 
@@ -181,6 +188,7 @@ void cmCursesMainForm::RePost()
     }
   else
     {
+    // If normal mode, count only non-advanced entries
     m_NumberOfVisibleEntries = 0;
     std::vector<cmCursesCacheEntryComposite*>::iterator it;
     for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
@@ -194,8 +202,11 @@ void cmCursesMainForm::RePost()
       }
     }
 
+  // Assign the fields: 3 for each entry: label, new entry marker
+  // ('*' or ' ') and entry widget
   m_Fields = new FIELD*[3*m_NumberOfVisibleEntries+1];
 
+  // Assign fields
   int j=0;
   std::vector<cmCursesCacheEntryComposite*>::iterator it;
   for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
@@ -223,32 +234,37 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
     FIELD* currentField = current_field(m_Form);
     cmCursesWidget* cw = reinterpret_cast<cmCursesWidget*>
       (field_userptr(currentField));
+    // If in edit mode, get out of it
     if ( cw->GetType() == cmCacheManager::STRING ||
 	 cw->GetType() == cmCacheManager::PATH   ||
 	 cw->GetType() == cmCacheManager::FILEPATH )
       {
       cmCursesStringWidget* sw = static_cast<cmCursesStringWidget*>(cw);
       sw->SetInEdit(false);
       }
+    // Delete the previous form
     unpost_form(m_Form);
     free_form(m_Form);
     m_Form = 0;
     }
+
+  // Wrong window size
   if ( width < cmCursesMainForm::MIN_WIDTH  || 
        height < cmCursesMainForm::MIN_HEIGHT )
     {
     return;
     }
 
-  height -= 6;
-  m_Height = height;
+  // Leave room for toolbar
+  height -= 7;
 
   if (m_AdvancedMode)
     {
     m_NumberOfVisibleEntries = m_Entries->size();
     }
   else
     {
+    // If normal, display only non-advanced entries
     m_NumberOfVisibleEntries = 0;
     std::vector<cmCursesCacheEntryComposite*>::iterator it;
     for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
@@ -262,8 +278,10 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
       }
     }
 
+  // Re-adjust the fields according to their place
   bool isNewPage;
   int i=0;
+  m_NumberOfPages = 1;
   std::vector<cmCursesCacheEntryComposite*>::iterator it;
   for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
     {
@@ -276,16 +294,24 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
     int page = (i / height) + 1;
     isNewPage = ( page > 1 ) && ( row == 1 );
 
+    if (isNewPage)
+      {
+      m_NumberOfPages++;
+      }
     (*it)->m_Label->Move(left, top+row-1, isNewPage);
     (*it)->m_IsNewLabel->Move(left+32, top+row-1, false);
     (*it)->m_Entry->Move(left+33, top+row-1, false);
+    (*it)->m_Entry->SetPage(m_NumberOfPages);
     i++;
     }
 
+  // Post the form
   m_Form = new_form(m_Fields);
   post_form(m_Form);
+  // Update toolbar
   this->UpdateStatusBar();
-  this->PrintKeys();
+  this->PrintKeys()
+;
   touchwin(stdscr); 
   refresh();
 }
@@ -299,28 +325,58 @@ void cmCursesMainForm::PrintKeys()
     {
     return;
     }
-  char firstLine[512], secondLine[512];
-  if (m_OkToGenerate)
-    {
-    sprintf(firstLine,  "C)onfigure                 G)enerate and Exit            H)elp");
-    }
-  else
+
+  // Give the current widget (if it exists), a chance to print keys
+  cmCursesWidget* cw = 0;
+  if (m_Form)
     {
-    sprintf(firstLine,  "C)onfigure                                               H)elp");
+    FIELD* currentField = current_field(m_Form);
+    cw = reinterpret_cast<cmCursesWidget*>(field_userptr(currentField));
     }
-  if (m_AdvancedMode)
+
+  if (cw && cw->PrintKeys())
     {
-    sprintf(secondLine, "Q)uit Without Generating   T)oggle Advanced Mode (On)");
     }
   else
     {
-    sprintf(secondLine, "Q)uit Without Generating   T)oggle Advanced Mode (Off)");
+    char firstLine[512], secondLine[512], thirdLine[512];
+    if (m_OkToGenerate)
+      {
+      sprintf(firstLine,  "Press [c] to configure     Press [g] to generate and exit");
+      }
+    else
+      {
+      sprintf(firstLine,  "Press [c] to configure");
+      }
+    if (m_AdvancedMode)
+      {
+      sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently On)");
+      }
+    else
+      {
+      sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently Off)");
+      }
+    
+    sprintf(secondLine, "Press [h] for help         Press [q] to quit without generating");
+
+
+    curses_move(y-4,0);
+    printw("Press [enter] to edit option");
+    curses_move(y-3,0);
+    printw(firstLine);
+    curses_move(y-2,0);
+    printw(secondLine);
+    curses_move(y-1,0);
+    printw(thirdLine);
+
+    if (cw)
+      {
+      sprintf(firstLine, "Page %d of %d", cw->GetPage(), m_NumberOfPages);
+      curses_move(0,65-strlen(firstLine)-1);
+      printw(firstLine);
+      }
     }
 
-  curses_move(y-2,0);
-  printw(firstLine);
-  curses_move(y-1,0);
-  printw(secondLine);
   pos_form_cursor(m_Form);
   
 }
@@ -331,6 +387,7 @@ void cmCursesMainForm::UpdateStatusBar()
 {
   int x,y;
   getmaxyx(stdscr, y, x);
+  // If window size is too small, display error and return
   if ( x < cmCursesMainForm::MIN_WIDTH  || 
        y < cmCursesMainForm::MIN_HEIGHT )
     {
@@ -343,12 +400,15 @@ void cmCursesMainForm::UpdateStatusBar()
     return;
     }
 
+  // Get the key of the current entry
   FIELD* cur = current_field(m_Form);
   int index = field_index(cur);
   cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
     m_Fields[index-2]));
   const char* curField = lbl->GetValue();
 
+  // Get the help string of the current entry
+  // and add it to the help string
   char help[128];
   const char* helpString;
   cmCacheManager::CacheEntry *entry = 
@@ -365,6 +425,8 @@ void cmCursesMainForm::UpdateStatusBar()
     }
 
 
+  // Join the key, help string and pad with spaces
+  // (or truncate) as necessary
   char bar[cmCursesMainForm::MAX_WIDTH];
   int i, curFieldLen = strlen(curField);
   int helpLen = strlen(help);
@@ -405,6 +467,7 @@ void cmCursesMainForm::UpdateStatusBar()
 
   bar[width] = '\0';
 
+  // Display CMake version info on the next line
   // We want to display this on the right
   char version[cmCursesMainForm::MAX_WIDTH];
   char vertmp[128];
@@ -415,11 +478,12 @@ void cmCursesMainForm::UpdateStatusBar()
   sprintf(version+sideSpace, "%s", vertmp);
   version[width] = '\0';
 
-  curses_move(y-4,0);
+  // Now print both lines
+  curses_move(y-5,0);
   attron(A_STANDOUT);
   printw(bar);
   attroff(A_STANDOUT);  
-  curses_move(y-3,0);
+  curses_move(y-4,0);
   printw(version);
   pos_form_cursor(m_Form);
 }
@@ -535,6 +599,8 @@ void cmCursesMainForm::FillCacheManagerFromUI()
 
 void cmCursesMainForm::HandleInput()
 {
+  int x,y;
+
   if (!m_Form)
     {
     return;
@@ -551,12 +617,31 @@ void cmCursesMainForm::HandleInput()
     this->PrintKeys();
     int key = getch();
 
+    getmaxyx(stdscr, y, x);
+    // If window too small, handle 'q' only
+    if ( x < cmCursesMainForm::MIN_WIDTH  || 
+	 y < cmCursesMainForm::MIN_HEIGHT )
+      {
+      // quit
+      if ( key == 'q' )
+	{
+	break;
+	}
+      else
+	{
+	continue;
+	}
+      }
+
     currentField = current_field(m_Form);
     currentWidget = reinterpret_cast<cmCursesWidget*>(field_userptr(
       currentField));
 
-    if (!currentWidget || !currentWidget->HandleInput(key, m_Form, stdscr))
+    // Ask the current widget if it wants to handle input
+    if (!currentWidget || !currentWidget->HandleInput(key, this, stdscr))
       {
+      // If the current widget does not want to handle input, 
+      // we handle it.
       sprintf(debugMessage, "Main form handling input, key: %d", key);
       cmCursesForm::LogMessage(debugMessage);
       // quit
@@ -627,7 +712,6 @@ void cmCursesMainForm::HandleInput()
       // display help
       else if ( key == 'h' )
 	{
-	int x,y;
 	getmaxyx(stdscr, y, x);
 
 	FIELD* cur = current_field(m_Form);
@@ -666,7 +750,6 @@ void cmCursesMainForm::HandleInput()
       // display last errors
       else if ( key == 'l' )
 	{
-	int x,y;
 	getmaxyx(stdscr, y, x);
 	cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
 								    "Errors which during last pass.");
@@ -687,7 +770,6 @@ void cmCursesMainForm::HandleInput()
 	  {
 	  m_AdvancedMode = true;
 	  }
-	int x,y;
 	getmaxyx(stdscr, y, x);
 	this->RePost();
 	this->Render(1, 1, x, y);
@@ -740,7 +822,6 @@ void cmCursesMainForm::HandleInput()
 	  nextVal = (reinterpret_cast<cmCursesWidget*>(field_userptr(nextCur))->GetValue());
 	  }
 
-	int x,y;
 	getmaxyx(stdscr, y, x);
 	this->RemoveEntry(lbl->GetValue());
 	this->RePost();