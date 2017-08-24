@@ -35,69 +35,69 @@ inline int ctrl(int z)
 
 cmCursesMainForm::cmCursesMainForm(std::vector<std::string> const& args,
                                    int initWidth) :
-  m_Args(args), m_InitialWidth(initWidth)
+  Args(args), InitialWidth(initWidth)
 {
-  m_NumberOfPages = 0;
-  m_Fields = 0;
-  m_Entries = 0;
-  m_AdvancedMode = false;
-  m_NumberOfVisibleEntries = 0;
-  m_OkToGenerate = false;
-  m_HelpMessage.push_back("Welcome to ccmake, curses based user interface for CMake.");
-  m_HelpMessage.push_back("");
-  m_HelpMessage.push_back(s_ConstHelpMessage);
-  m_CMakeInstance = new cmake;
+  this->NumberOfPages = 0;
+  this->Fields = 0;
+  this->Entries = 0;
+  this->AdvancedMode = false;
+  this->NumberOfVisibleEntries = 0;
+  this->OkToGenerate = false;
+  this->HelpMessage.push_back("Welcome to ccmake, curses based user interface for CMake.");
+  this->HelpMessage.push_back("");
+  this->HelpMessage.push_back(s_ConstHelpMessage);
+  this->CMakeInstance = new cmake;
 
   // create the arguments for the cmake object
-  std::string whereCMake = cmSystemTools::GetProgramPath(m_Args[0].c_str());
+  std::string whereCMake = cmSystemTools::GetProgramPath(this->Args[0].c_str());
   whereCMake += "/cmake";
-  m_Args[0] = whereCMake;
-  m_CMakeInstance->SetArgs(m_Args);
-  m_CMakeInstance->SetCMakeCommand(whereCMake.c_str());
-  m_SearchString = "";
-  m_OldSearchString = "";
-  m_SearchMode = false;
+  this->Args[0] = whereCMake;
+  this->CMakeInstance->SetArgs(this->Args);
+  this->CMakeInstance->SetCMakeCommand(whereCMake.c_str());
+  this->SearchString = "";
+  this->OldSearchString = "";
+  this->SearchMode = false;
 }
 
 cmCursesMainForm::~cmCursesMainForm()
 {
-  if (m_Form)
+  if (this->Form)
     {
-    unpost_form(m_Form);
-    free_form(m_Form);
-    m_Form = 0;
+    unpost_form(this->Form);
+    free_form(this->Form);
+    this->Form = 0;
     }
-  delete[] m_Fields;
+  delete[] this->Fields;
 
   // Clean-up composites
-  if (m_Entries)
+  if (this->Entries)
     {
     std::vector<cmCursesCacheEntryComposite*>::iterator it;
-    for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+    for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
       {
       delete *it;
       }
     }
-  delete m_Entries;
-  if (this->m_CMakeInstance)
+  delete this->Entries;
+  if (this->CMakeInstance)
     {
-    delete this->m_CMakeInstance;
-    this->m_CMakeInstance = 0;
+    delete this->CMakeInstance;
+    this->CMakeInstance = 0;
     }  
 }
 
 // See if a cache entry is in the list of entries in the ui.
 bool cmCursesMainForm::LookForCacheEntry(const char* key)
 {
-  if (!key || !m_Entries)
+  if (!key || !this->Entries)
     {
     return false;
     }
 
   std::vector<cmCursesCacheEntryComposite*>::iterator it;
-  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+  for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
     {
-    if (!strcmp(key, (*it)->m_Key.c_str()))
+    if (!strcmp(key, (*it)->Key.c_str()))
       {
       return true;
       }
@@ -113,12 +113,12 @@ void cmCursesMainForm::InitializeUI()
   // which contain labels, entries and new entry markers
   std::vector<cmCursesCacheEntryComposite*>* newEntries =
     new std::vector<cmCursesCacheEntryComposite*>;
-  newEntries->reserve(this->m_CMakeInstance->GetCacheManager()->GetSize());
+  newEntries->reserve(this->CMakeInstance->GetCacheManager()->GetSize());
 
   // Count non-internal and non-static entries
   int count=0;
   for(cmCacheManager::CacheIterator i = 
-        this->m_CMakeInstance->GetCacheManager()->NewIterator();
+        this->CMakeInstance->GetCacheManager()->NewIterator();
       !i.IsAtEnd(); i.Next())
     {
     if ( i.GetType() != cmCacheManager::INTERNAL &&
@@ -129,15 +129,15 @@ void cmCursesMainForm::InitializeUI()
       }
     }
 
-  int entrywidth = m_InitialWidth - 35;
+  int entrywidth = this->InitialWidth - 35;
 
   cmCursesCacheEntryComposite* comp;
   if ( count == 0 )
     {
     // If cache is empty, display a label saying so and a
     // dummy entry widget (does not respond to input)
     comp = new cmCursesCacheEntryComposite("EMPTY CACHE", 30, 30);
-    comp->m_Entry = new cmCursesDummyWidget(1, 1, 1, 1);
+    comp->Entry = new cmCursesDummyWidget(1, 1, 1, 1);
     newEntries->push_back(comp);
     }
   else
@@ -146,7 +146,7 @@ void cmCursesMainForm::InitializeUI()
 
     // First add entries which are new
     for(cmCacheManager::CacheIterator i = 
-          this->m_CMakeInstance->GetCacheManager()->NewIterator();
+          this->CMakeInstance->GetCacheManager()->NewIterator();
         !i.IsAtEnd(); i.Next())
       {
       const char* key = i.GetName();
@@ -162,13 +162,13 @@ void cmCursesMainForm::InitializeUI()
         newEntries->push_back(new cmCursesCacheEntryComposite(key, i,
                                                               true, 30,
                                                               entrywidth));
-        m_OkToGenerate = false;
+        this->OkToGenerate = false;
         }
       }
 
     // then add entries which are old
     for(cmCacheManager::CacheIterator i = 
-          this->m_CMakeInstance->GetCacheManager()->NewIterator();
+          this->CMakeInstance->GetCacheManager()->NewIterator();
         !i.IsAtEnd(); i.Next())
       {
       const char* key = i.GetName();
@@ -189,17 +189,17 @@ void cmCursesMainForm::InitializeUI()
     }
   
   // Clean old entries
-  if (m_Entries)
+  if (this->Entries)
     {
     // Have to call delete on each pointer
     std::vector<cmCursesCacheEntryComposite*>::iterator it;
-    for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+    for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
       {
       delete *it;
       }
     }
-  delete m_Entries;
-  m_Entries = newEntries;
+  delete this->Entries;
+  this->Entries = newEntries;
   
   // Compute fields from composites
   this->RePost();
@@ -209,71 +209,71 @@ void cmCursesMainForm::InitializeUI()
 void cmCursesMainForm::RePost()
 {
   // Create the fields to be passed to the form.
-  if (m_Form)
+  if (this->Form)
     {
-    unpost_form(m_Form);
-    free_form(m_Form);
-    m_Form = 0;
+    unpost_form(this->Form);
+    free_form(this->Form);
+    this->Form = 0;
     }
-  delete[] m_Fields;
+  delete[] this->Fields;
 
-  if (m_AdvancedMode)
+  if (this->AdvancedMode)
     {
-    m_NumberOfVisibleEntries = m_Entries->size();
+    this->NumberOfVisibleEntries = this->Entries->size();
     }
   else
     {
     // If normal mode, count only non-advanced entries
-    m_NumberOfVisibleEntries = 0;
+    this->NumberOfVisibleEntries = 0;
     std::vector<cmCursesCacheEntryComposite*>::iterator it;
-    for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+    for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
       {
       cmCacheManager::CacheIterator mit = 
-        this->m_CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
-      if (mit.IsAtEnd() || !m_AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
+        this->CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
+      if (mit.IsAtEnd() || !this->AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
         {
         continue;
         }
-      m_NumberOfVisibleEntries++;
+      this->NumberOfVisibleEntries++;
       }
     }
 
   // Assign the fields: 3 for each entry: label, new entry marker
   // ('*' or ' ') and entry widget
-  m_Fields = new FIELD*[3*m_NumberOfVisibleEntries+1];
+  this->Fields = new FIELD*[3*this->NumberOfVisibleEntries+1];
   int cc;
-  for ( cc = 0; cc < 3 * m_NumberOfVisibleEntries+1; cc ++ )
+  for ( cc = 0; cc < 3 * this->NumberOfVisibleEntries+1; cc ++ )
     {
-    m_Fields[cc] = 0;
+    this->Fields[cc] = 0;
     }
 
   // Assign fields
   int j=0;
   std::vector<cmCursesCacheEntryComposite*>::iterator it;
-  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+  for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
     {
     cmCacheManager::CacheIterator mit = 
-      this->m_CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
-    if (mit.IsAtEnd() || !m_AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
+      this->CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
+    if (mit.IsAtEnd() || !this->AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
       {
       continue;
       }
-    m_Fields[3*j]    = (*it)->m_Label->m_Field;
-    m_Fields[3*j+1]  = (*it)->m_IsNewLabel->m_Field;
-    m_Fields[3*j+2]  = (*it)->m_Entry->m_Field;
+    this->Fields[3*j]    = (*it)->Label->Field;
+    this->Fields[3*j+1]  = (*it)->IsNewLabel->Field;
+    this->Fields[3*j+2]  = (*it)->Entry->Field;
     j++;
     }
 
   // Has to be null terminated.
-  m_Fields[3*m_NumberOfVisibleEntries] = 0;
+  this->Fields[3*this->NumberOfVisibleEntries] = 0;
 }
 
 void cmCursesMainForm::Render(int left, int top, int width, int height)
 {
 
-  if (m_Form)
+  if (this->Form)
     {
-    FIELD* currentField = current_field(m_Form);
+    FIELD* currentField = current_field(this->Form);
     cmCursesWidget* cw = reinterpret_cast<cmCursesWidget*>
       (field_userptr(currentField));
     // If in edit mode, get out of it
@@ -285,14 +285,14 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
       sw->SetInEdit(false);
       }
     // Delete the previous form
-    unpost_form(m_Form);
-    free_form(m_Form);
-    m_Form = 0;
+    unpost_form(this->Form);
+    free_form(this->Form);
+    this->Form = 0;
     }
 
   // Wrong window size
   if ( width < cmCursesMainForm::MIN_WIDTH  || 
-       width < m_InitialWidth               ||
+       width < this->InitialWidth               ||
        height < cmCursesMainForm::MIN_HEIGHT )
     {
     return;
@@ -301,37 +301,37 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
   // Leave room for toolbar
   height -= 7;
 
-  if (m_AdvancedMode)
+  if (this->AdvancedMode)
     {
-    m_NumberOfVisibleEntries = m_Entries->size();
+    this->NumberOfVisibleEntries = this->Entries->size();
     }
   else
     {
     // If normal, display only non-advanced entries
-    m_NumberOfVisibleEntries = 0;
+    this->NumberOfVisibleEntries = 0;
     std::vector<cmCursesCacheEntryComposite*>::iterator it;
-    for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+    for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
       {
       cmCacheManager::CacheIterator mit = 
-        this->m_CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
-      if (mit.IsAtEnd() || !m_AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
+        this->CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
+      if (mit.IsAtEnd() || !this->AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
         {
         continue;
         }
-      m_NumberOfVisibleEntries++;
+      this->NumberOfVisibleEntries++;
       }
     }
 
   // Re-adjust the fields according to their place
   bool isNewPage;
   int i=0;
-  m_NumberOfPages = 1;
+  this->NumberOfPages = 1;
   std::vector<cmCursesCacheEntryComposite*>::iterator it;
-  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+  for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
     {
     cmCacheManager::CacheIterator mit = 
-      this->m_CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
-    if (mit.IsAtEnd() || !m_AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
+      this->CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
+    if (mit.IsAtEnd() || !this->AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
       {
       continue;
       }
@@ -341,18 +341,18 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
 
     if (isNewPage)
       {
-      m_NumberOfPages++;
+      this->NumberOfPages++;
       }
-    (*it)->m_Label->Move(left, top+row-1, isNewPage);
-    (*it)->m_IsNewLabel->Move(left+32, top+row-1, false);
-    (*it)->m_Entry->Move(left+33, top+row-1, false);
-    (*it)->m_Entry->SetPage(m_NumberOfPages);
+    (*it)->Label->Move(left, top+row-1, isNewPage);
+    (*it)->IsNewLabel->Move(left+32, top+row-1, false);
+    (*it)->Entry->Move(left+33, top+row-1, false);
+    (*it)->Entry->SetPage(this->NumberOfPages);
     i++;
     }
 
   // Post the form
-  m_Form = new_form(m_Fields);
-  post_form(m_Form);
+  this->Form = new_form(this->Fields);
+  post_form(this->Form);
   // Update toolbar
   this->UpdateStatusBar();
   this->PrintKeys();
@@ -366,17 +366,17 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
   int x,y;
   getmaxyx(stdscr, y, x);
   if ( x < cmCursesMainForm::MIN_WIDTH  || 
-       x < m_InitialWidth               ||
+       x < this->InitialWidth               ||
        y < cmCursesMainForm::MIN_HEIGHT )
     {
     return;
     }
 
   // Give the current widget (if it exists), a chance to print keys
   cmCursesWidget* cw = 0;
-  if (m_Form)
+  if (this->Form)
     {
-    FIELD* currentField = current_field(m_Form);
+    FIELD* currentField = current_field(this->Form);
     cw = reinterpret_cast<cmCursesWidget*>(field_userptr(currentField));
     }
 
@@ -403,7 +403,7 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
     }
   else
     {
-    if (m_OkToGenerate)
+    if (this->OkToGenerate)
       {
       sprintf(firstLine,  
               "Press [c] to configure     Press [g] to generate and exit");
@@ -412,7 +412,7 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
       {
       sprintf(firstLine,  "Press [c] to configure                                   ");
       }
-    if (m_AdvancedMode)
+    if (this->AdvancedMode)
       {
       sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently On)");
       }
@@ -441,13 +441,13 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
 
   if (cw)
     {
-    sprintf(firstLine, "Page %d of %d", cw->GetPage(), m_NumberOfPages);
+    sprintf(firstLine, "Page %d of %d", cw->GetPage(), this->NumberOfPages);
     curses_move(0,65-strlen(firstLine)-1);
     printw(firstLine);
     }
 //    }
 
-  pos_form_cursor(m_Form);
+  pos_form_cursor(this->Form);
   
 }
 
@@ -459,28 +459,28 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   getmaxyx(stdscr, y, x);
   // If window size is too small, display error and return
   if ( x < cmCursesMainForm::MIN_WIDTH  || 
-       x < m_InitialWidth               ||
+       x < this->InitialWidth               ||
        y < cmCursesMainForm::MIN_HEIGHT )
     {
     curses_clear();
     curses_move(0,0);
     char fmt[] = "Window is too small. A size of at least %dx%d is required.";
     printw(fmt,
-           (cmCursesMainForm::MIN_WIDTH < m_InitialWidth ?
-            m_InitialWidth : cmCursesMainForm::MIN_WIDTH), 
+           (cmCursesMainForm::MIN_WIDTH < this->InitialWidth ?
+            this->InitialWidth : cmCursesMainForm::MIN_WIDTH), 
            cmCursesMainForm::MIN_HEIGHT);
     touchwin(stdscr); 
     wrefresh(stdscr); 
     return;
     }
 
   // Get the key of the current entry
-  FIELD* cur = current_field(m_Form);
+  FIELD* cur = current_field(this->Form);
   int findex = field_index(cur);
   cmCursesWidget* lbl = 0;
   if ( findex >= 0 )
     {
-    lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(m_Fields[findex-2]));
+    lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(this->Fields[findex-2]));
     }
   char help[128] = "";
   const char* curField = "";
@@ -491,7 +491,7 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
     // Get the help string of the current entry
     // and add it to the help string
     cmCacheManager::CacheIterator it = 
-      this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
+      this->CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
     if (!it.IsAtEnd())
       {
       const char* hs = it.GetProperty("HELPSTRING");
@@ -594,7 +594,7 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   attroff(A_STANDOUT);  
   curses_move(y-4,0);
   printw(version);
-  pos_form_cursor(m_Form);
+  pos_form_cursor(this->Form);
 }
 
 void cmCursesMainForm::UpdateProgressOld(const char *msg, float prog, void*)
@@ -639,51 +639,51 @@ int cmCursesMainForm::Configure(int noconfigure)
   this->PrintKeys(1);
   touchwin(stdscr); 
   refresh();
-  this->m_CMakeInstance->SetProgressCallback(cmCursesMainForm::UpdateProgress, this);
+  this->CMakeInstance->SetProgressCallback(cmCursesMainForm::UpdateProgress, this);
 
   // always save the current gui values to disk
   this->FillCacheManagerFromUI();
-  this->m_CMakeInstance->GetCacheManager()->SaveCache(
-    m_CMakeInstance->GetHomeOutputDirectory());
+  this->CMakeInstance->GetCacheManager()->SaveCache(
+    this->CMakeInstance->GetHomeOutputDirectory());
   this->LoadCache(0);
   
   // Get rid of previous errors
-  m_Errors = std::vector<std::string>();
+  this->Errors = std::vector<std::string>();
 
   // run the generate process
-  m_OkToGenerate = true;
+  this->OkToGenerate = true;
   int retVal;
   if ( noconfigure )
     {
-    retVal = this->m_CMakeInstance->DoPreConfigureChecks();
-    m_OkToGenerate = false;
+    retVal = this->CMakeInstance->DoPreConfigureChecks();
+    this->OkToGenerate = false;
     if ( retVal > 0 )
       {
       retVal = 0;
       }
     }
   else
     {
-    retVal = this->m_CMakeInstance->Configure();
+    retVal = this->CMakeInstance->Configure();
     }
-  this->m_CMakeInstance->SetProgressCallback(0, 0);
+  this->CMakeInstance->SetProgressCallback(0, 0);
 
   keypad(stdscr,TRUE); /* Use key symbols as 
                           KEY_DOWN*/ 
 
-  if( retVal != 0 || !m_Errors.empty())
+  if( retVal != 0 || !this->Errors.empty())
     {
     // see if there was an error
     if(cmSystemTools::GetErrorOccuredFlag())
       {
-      m_OkToGenerate = false;
+      this->OkToGenerate = false;
       }
     // reset error condition
     cmSystemTools::ResetErrorOccuredFlag();
     int xx,yy;
     getmaxyx(stdscr, yy, xx);
     cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(
-      m_Errors,
+      this->Errors,
       cmSystemTools::GetErrorOccuredFlag() ? "Errors occurred during the last pass." :
                                              "CMake produced the following output.");
     CurrentForm = msgs;
@@ -715,30 +715,30 @@ int cmCursesMainForm::Generate()
   this->PrintKeys(1);
   touchwin(stdscr);
   refresh();
-  this->m_CMakeInstance->SetProgressCallback(cmCursesMainForm::UpdateProgress, this);
+  this->CMakeInstance->SetProgressCallback(cmCursesMainForm::UpdateProgress, this);
 
   // Get rid of previous errors
-  m_Errors = std::vector<std::string>();
+  this->Errors = std::vector<std::string>();
 
   // run the generate process
-  int retVal = this->m_CMakeInstance->Generate();
+  int retVal = this->CMakeInstance->Generate();
 
-  this->m_CMakeInstance->SetProgressCallback(0, 0);
+  this->CMakeInstance->SetProgressCallback(0, 0);
   keypad(stdscr,TRUE); /* Use key symbols as 
                           KEY_DOWN*/ 
 
-  if( retVal != 0 || !m_Errors.empty())
+  if( retVal != 0 || !this->Errors.empty())
     {
     // see if there was an error
     if(cmSystemTools::GetErrorOccuredFlag())
       {
-      m_OkToGenerate = false;
+      this->OkToGenerate = false;
       }
     // reset error condition
     cmSystemTools::ResetErrorOccuredFlag();
     int xx,yy;
     getmaxyx(stdscr, yy, xx);
-    cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
+    cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(this->Errors,
                                                                 "Errors occurred during the last pass.");
     CurrentForm = msgs;
     msgs->Render(1,1,xx,yy);
@@ -761,7 +761,7 @@ int cmCursesMainForm::Generate()
 
 void cmCursesMainForm::AddError(const char* message, const char*)
 {
-  m_Errors.push_back(message);
+  this->Errors.push_back(message);
 }
 
 void cmCursesMainForm::RemoveEntry(const char* value)
@@ -772,12 +772,12 @@ void cmCursesMainForm::RemoveEntry(const char* value)
     }
 
   std::vector<cmCursesCacheEntryComposite*>::iterator it;
-  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+  for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
     {
     const char* val = (*it)->GetValue();
     if (  val && !strcmp(value, val) )
       {
-      m_Entries->erase(it);
+      this->Entries->erase(it);
       break;
       }
     }
@@ -786,16 +786,16 @@ void cmCursesMainForm::RemoveEntry(const char* value)
 // copy from the list box to the cache manager
 void cmCursesMainForm::FillCacheManagerFromUI()
 {   
-  int size = m_Entries->size();
+  int size = this->Entries->size();
   for(int i=0; i < size; i++)
     {
     cmCacheManager::CacheIterator it = 
-      this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(
-        (*m_Entries)[i]->m_Key.c_str());
+      this->CMakeInstance->GetCacheManager()->GetCacheIterator(
+        (*this->Entries)[i]->Key.c_str());
     if (!it.IsAtEnd())
       {
       std::string oldValue = it.GetValue();
-      std::string newValue = (*m_Entries)[i]->m_Entry->GetValue();
+      std::string newValue = (*this->Entries)[i]->Entry->GetValue();
       std::string fixedOldValue;
       std::string fixedNewValue;
       this->FixValue(it.GetType(), oldValue, fixedOldValue);
@@ -838,7 +838,7 @@ void cmCursesMainForm::HandleInput()
 {
   int x=0,y=0;
 
-  if (!m_Form)
+  if (!this->Form)
     {
     return;
     }
@@ -852,9 +852,9 @@ void cmCursesMainForm::HandleInput()
     {
     this->UpdateStatusBar();
     this->PrintKeys();
-    if ( m_SearchMode )
+    if ( this->SearchMode )
       {
-      std::string searchstr = "Search: " + m_SearchString;
+      std::string searchstr = "Search: " + this->SearchString;
       this->UpdateStatusBar( searchstr.c_str() );
       this->PrintKeys(1);
       curses_move(y-5,searchstr.size());
@@ -880,60 +880,60 @@ void cmCursesMainForm::HandleInput()
         }
       }
 
-    currentField = current_field(m_Form);
+    currentField = current_field(this->Form);
     currentWidget = reinterpret_cast<cmCursesWidget*>(field_userptr(
       currentField));
 
     bool widgetHandled=false;
 
-    if ( m_SearchMode )
+    if ( this->SearchMode )
       {
       if ( key == 10 || key == KEY_ENTER )
         {
-        m_SearchMode = false;
-        if ( m_SearchString.size() > 0 )
+        this->SearchMode = false;
+        if ( this->SearchString.size() > 0 )
           {
-          this->JumpToCacheEntry(-1, m_SearchString.c_str());
-          m_OldSearchString = m_SearchString;
+          this->JumpToCacheEntry(-1, this->SearchString.c_str());
+          this->OldSearchString = this->SearchString;
           }
-        m_SearchString = "";
+        this->SearchString = "";
         }
       /*
       else if ( key == KEY_ESCAPE )
         {
-        m_SearchMode = false;
+        this->SearchMode = false;
         }
       */
       else if ( key >= 'a' && key <= 'z' || 
                 key >= 'A' && key <= 'Z' ||
                 key >= '0' && key <= '9' ||
                 key == '_' )
         {
-        if ( m_SearchString.size() < static_cast<std::string::size_type>(x-10) )
+        if ( this->SearchString.size() < static_cast<std::string::size_type>(x-10) )
           {
-          m_SearchString += key;
+          this->SearchString += key;
           }
         }
       else if ( key == ctrl('h') || key == KEY_BACKSPACE || key == KEY_DC )
         {
-        if ( m_SearchString.size() > 0 )
+        if ( this->SearchString.size() > 0 )
           {
-          m_SearchString.resize(m_SearchString.size()-1);
+          this->SearchString.resize(this->SearchString.size()-1);
           }
         }
       }
-    else if (currentWidget && !m_SearchMode)
+    else if (currentWidget && !this->SearchMode)
       {
       // Ask the current widget if it wants to handle input
       widgetHandled = currentWidget->HandleInput(key, this, stdscr);
       if (widgetHandled)
         {
-        m_OkToGenerate = false;
+        this->OkToGenerate = false;
         this->UpdateStatusBar();
         this->PrintKeys();
         }
       }
-    if ((!currentWidget || !widgetHandled) && !m_SearchMode)
+    if ((!currentWidget || !widgetHandled) && !this->SearchMode)
       {
       // If the current widget does not want to handle input, 
       // we handle it.
@@ -951,19 +951,19 @@ void cmCursesMainForm::HandleInput()
       // (index always corresponds to the value field)
       else if ( key == KEY_DOWN || key == ctrl('n') )
         {
-        FIELD* cur = current_field(m_Form);
+        FIELD* cur = current_field(this->Form);
         int findex = field_index(cur);
-        if ( findex == 3*m_NumberOfVisibleEntries-1 )
+        if ( findex == 3*this->NumberOfVisibleEntries-1 )
           {
           continue;
           }
-        if (new_page(m_Fields[findex+1]))
+        if (new_page(this->Fields[findex+1]))
           {
-          form_driver(m_Form, REQ_NEXT_PAGE);
+          form_driver(this->Form, REQ_NEXT_PAGE);
           }
         else
           {
-          form_driver(m_Form, REQ_NEXT_FIELD);
+          form_driver(this->Form, REQ_NEXT_FIELD);
           }
         }
       // if not beginning of page, previous field, otherwise previous page
@@ -973,31 +973,31 @@ void cmCursesMainForm::HandleInput()
       // (index always corresponds to the value field)
       else if ( key == KEY_UP || key == ctrl('p') )
         {
-        FIELD* cur = current_field(m_Form);
+        FIELD* cur = current_field(this->Form);
         int findex = field_index(cur);
         if ( findex == 2 )
           {
           continue;
           }
-        if ( new_page(m_Fields[findex-2]) )
+        if ( new_page(this->Fields[findex-2]) )
           {
-          form_driver(m_Form, REQ_PREV_PAGE);
-          set_current_field(m_Form, m_Fields[findex-3]);
+          form_driver(this->Form, REQ_PREV_PAGE);
+          set_current_field(this->Form, this->Fields[findex-3]);
           }
         else
           {
-          form_driver(m_Form, REQ_PREV_FIELD);
+          form_driver(this->Form, REQ_PREV_FIELD);
           }
         }
       // pg down
       else if ( key == KEY_NPAGE || key == ctrl('d') )
         {
-        form_driver(m_Form, REQ_NEXT_PAGE);
+        form_driver(this->Form, REQ_NEXT_PAGE);
         }
       // pg up
       else if ( key == KEY_PPAGE || key == ctrl('u') )
         {
-        form_driver(m_Form, REQ_PREV_PAGE);
+        form_driver(this->Form, REQ_PREV_PAGE);
         }
       // configure
       else if ( key == 'c' )
@@ -1009,14 +1009,14 @@ void cmCursesMainForm::HandleInput()
         {
         getmaxyx(stdscr, y, x);
 
-        FIELD* cur = current_field(m_Form);
+        FIELD* cur = current_field(this->Form);
         int findex = field_index(cur);
         cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
-          m_Fields[findex-2]));
+          this->Fields[findex-2]));
         const char* curField = lbl->GetValue();
         const char* helpString=0;
         cmCacheManager::CacheIterator it = 
-          this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
+          this->CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
         if (!it.IsAtEnd())
           {
           helpString = it.GetProperty("HELPSTRING");
@@ -1026,28 +1026,28 @@ void cmCursesMainForm::HandleInput()
           char* message = new char[strlen(curField)+strlen(helpString)
                                   +strlen("Current option is: \n Help string for this option is: \n")+10];
           sprintf(message,"Current option is: %s\nHelp string for this option is: %s\n", curField, helpString);
-          m_HelpMessage[1] = message;
+          this->HelpMessage[1] = message;
           delete[] message;
           }
         else
           {
-          m_HelpMessage[1] = "";
+          this->HelpMessage[1] = "";
           }
 
-        cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_HelpMessage,
+        cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(this->HelpMessage,
                                                                     "Help.");
         CurrentForm = msgs;
         msgs->Render(1,1,x,y);
         msgs->HandleInput();
         CurrentForm = this; 
         this->Render(1,1,x,y);
-        set_current_field(m_Form, cur);
+        set_current_field(this->Form, cur);
         }
       // display last errors
       else if ( key == 'l' )
         {
         getmaxyx(stdscr, y, x);
-        cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
+        cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(this->Errors,
                                                                     "Errors occurred during the last pass.");
         CurrentForm = msgs;
         msgs->Render(1,1,x,y);
@@ -1057,29 +1057,29 @@ void cmCursesMainForm::HandleInput()
         }
       else if ( key == '/' )
         {
-        m_SearchMode = true;
+        this->SearchMode = true;
         this->UpdateStatusBar("Search");
         this->PrintKeys(1);
         touchwin(stdscr);
         refresh();
         }
       else if ( key == 'n' )
         {
-        if ( m_OldSearchString.size() > 0 )
+        if ( this->OldSearchString.size() > 0 )
           {
-          this->JumpToCacheEntry(-1, m_OldSearchString.c_str());
+          this->JumpToCacheEntry(-1, this->OldSearchString.c_str());
           }
         }
       // switch advanced on/off
       else if ( key == 't' )
         {
-        if (m_AdvancedMode)
+        if (this->AdvancedMode)
           {
-          m_AdvancedMode = false;
+          this->AdvancedMode = false;
           }
         else
           {
-          m_AdvancedMode = true;
+          this->AdvancedMode = true;
           }
         getmaxyx(stdscr, y, x);
         this->RePost();
@@ -1088,17 +1088,17 @@ void cmCursesMainForm::HandleInput()
       // generate and exit
       else if ( key == 'g' )
         {
-        if ( m_OkToGenerate )
+        if ( this->OkToGenerate )
           {
           this->Generate();
           break;
           }
         }
       // delete cache entry
-      else if ( key == 'd' && m_NumberOfVisibleEntries )
+      else if ( key == 'd' && this->NumberOfVisibleEntries )
         {
-        m_OkToGenerate = false;
-        FIELD* cur = current_field(m_Form);
+        this->OkToGenerate = false;
+        FIELD* cur = current_field(this->Form);
         int findex = field_index(cur);
 
         // make the next or prev. current field after deletion
@@ -1111,13 +1111,13 @@ void cmCursesMainForm::HandleInput()
           {
           nextCur=0;
           }
-        else if ( findex == 3*m_NumberOfVisibleEntries-1 )
+        else if ( findex == 3*this->NumberOfVisibleEntries-1 )
           {
-          nextCur = m_Fields[findex-5];
+          nextCur = this->Fields[findex-5];
           }
         else
           {
-          nextCur = m_Fields[findex+1];
+          nextCur = this->Fields[findex+1];
           }
 
         // Get the label widget
@@ -1126,10 +1126,10 @@ void cmCursesMainForm::HandleInput()
         // (findex always corresponds to the value field)
         cmCursesWidget* lbl 
           = reinterpret_cast<cmCursesWidget*>(
-            field_userptr(m_Fields[findex-2]));
+            field_userptr(this->Fields[findex-2]));
         if ( lbl )
           {
-          this->m_CMakeInstance->GetCacheManager()->RemoveCacheEntry(lbl->GetValue());
+          this->CMakeInstance->GetCacheManager()->RemoveCacheEntry(lbl->GetValue());
 
           std::string nextVal;
           if (nextCur)
@@ -1147,17 +1147,17 @@ void cmCursesMainForm::HandleInput()
             // make the next or prev. current field after deletion
             nextCur = 0;
             std::vector<cmCursesCacheEntryComposite*>::iterator it;
-            for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+            for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
               {
-              if (nextVal == (*it)->m_Key)
+              if (nextVal == (*it)->Key)
                 {
-                nextCur = (*it)->m_Entry->m_Field;
+                nextCur = (*it)->Entry->Field;
                 }
               }
 
             if (nextCur)
               {
-              set_current_field(m_Form, nextCur);
+              set_current_field(this->Form, nextCur);
               }
             }
           }
@@ -1172,13 +1172,13 @@ void cmCursesMainForm::HandleInput()
 int cmCursesMainForm::LoadCache(const char *)
 
 {
-  int r = m_CMakeInstance->LoadCache(); 
+  int r = this->CMakeInstance->LoadCache(); 
   if(r < 0)
     {
     return r;
     }
-  m_CMakeInstance->SetCacheArgs(m_Args);
-  m_CMakeInstance->PreLoadCMakeFiles();
+  this->CMakeInstance->SetCacheArgs(this->Args);
+  this->CMakeInstance->PreLoadCMakeFiles();
   return r;
 }
   
@@ -1190,15 +1190,15 @@ void cmCursesMainForm::JumpToCacheEntry(int idx, const char* astr)
     str = cmSystemTools::LowerCase(astr);
     }
 
-  if ( idx > m_NumberOfVisibleEntries )
+  if ( idx > this->NumberOfVisibleEntries )
     {
     return;
     }
   if ( idx < 0 && str.size() == 0)
     {
     return;
     }
-  FIELD* cur = current_field(m_Form);
+  FIELD* cur = current_field(this->Form);
   int start_index = field_index(cur);
   int findex = start_index;
   while ( (findex / 3) != idx ) 
@@ -1208,7 +1208,7 @@ void cmCursesMainForm::JumpToCacheEntry(int idx, const char* astr)
       cmCursesWidget* lbl = 0;
       if ( findex >= 0 )
         {
-        lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(m_Fields[findex-2]));
+        lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(this->Fields[findex-2]));
         }
       if ( lbl )
         {
@@ -1223,27 +1223,27 @@ void cmCursesMainForm::JumpToCacheEntry(int idx, const char* astr)
           }
         }
       }
-    if ( findex >= 3* m_NumberOfVisibleEntries-1 )
+    if ( findex >= 3* this->NumberOfVisibleEntries-1 )
       {
-      set_current_field(m_Form, m_Fields[2]);
+      set_current_field(this->Form, this->Fields[2]);
       }
-    else if (new_page(m_Fields[findex+1]))
+    else if (new_page(this->Fields[findex+1]))
       {
-      form_driver(m_Form, REQ_NEXT_PAGE);
+      form_driver(this->Form, REQ_NEXT_PAGE);
       }
     else
       {
-      form_driver(m_Form, REQ_NEXT_FIELD);
+      form_driver(this->Form, REQ_NEXT_FIELD);
       }
     /*
     char buffer[1024];
-    sprintf(buffer, "Line: %d != %d / %d\n", findex, idx, m_NumberOfVisibleEntries);
+    sprintf(buffer, "Line: %d != %d / %d\n", findex, idx, this->NumberOfVisibleEntries);
     touchwin(stdscr); 
     refresh();
     this->UpdateStatusBar( buffer );
     usleep(100000);
     */
-    cur = current_field(m_Form);
+    cur = current_field(this->Form);
     findex = field_index(cur);
     if ( findex == start_index )
       {