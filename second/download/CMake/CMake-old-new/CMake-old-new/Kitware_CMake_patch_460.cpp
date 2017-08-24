@@ -27,7 +27,7 @@
 inline int ctrl(int z)
 {
     return (z&037);
-} 
+}
 
 cmCursesMainForm::cmCursesMainForm(std::vector<std::string> const& args,
                                    int initWidth) :
@@ -80,7 +80,7 @@ cmCursesMainForm::~cmCursesMainForm()
     {
     delete this->CMakeInstance;
     this->CMakeInstance = 0;
-    }  
+    }
 }
 
 // See if a cache entry is in the list of entries in the ui.
@@ -99,7 +99,7 @@ bool cmCursesMainForm::LookForCacheEntry(const char* key)
       return true;
       }
     }
-  
+
   return false;
 }
 
@@ -114,7 +114,7 @@ void cmCursesMainForm::InitializeUI()
 
   // Count non-internal and non-static entries
   int count=0;
-  for(cmCacheManager::CacheIterator i = 
+  for(cmCacheManager::CacheIterator i =
         this->CMakeInstance->GetCacheManager()->NewIterator();
       !i.IsAtEnd(); i.Next())
     {
@@ -142,12 +142,12 @@ void cmCursesMainForm::InitializeUI()
     // Create the composites.
 
     // First add entries which are new
-    for(cmCacheManager::CacheIterator i = 
+    for(cmCacheManager::CacheIterator i =
           this->CMakeInstance->GetCacheManager()->NewIterator();
         !i.IsAtEnd(); i.Next())
       {
       const char* key = i.GetName();
-      if ( i.GetType() == cmCacheManager::INTERNAL || 
+      if ( i.GetType() == cmCacheManager::INTERNAL ||
            i.GetType() == cmCacheManager::STATIC ||
            i.GetType() == cmCacheManager::UNINITIALIZED )
         {
@@ -164,12 +164,12 @@ void cmCursesMainForm::InitializeUI()
       }
 
     // then add entries which are old
-    for(cmCacheManager::CacheIterator i = 
+    for(cmCacheManager::CacheIterator i =
           this->CMakeInstance->GetCacheManager()->NewIterator();
         !i.IsAtEnd(); i.Next())
       {
       const char* key = i.GetName();
-      if ( i.GetType() == cmCacheManager::INTERNAL || 
+      if ( i.GetType() == cmCacheManager::INTERNAL ||
            i.GetType() == cmCacheManager::STATIC ||
            i.GetType() == cmCacheManager::UNINITIALIZED )
         {
@@ -184,7 +184,7 @@ void cmCursesMainForm::InitializeUI()
         }
       }
     }
-  
+
   // Clean old entries
   if (this->Entries)
     {
@@ -197,7 +197,7 @@ void cmCursesMainForm::InitializeUI()
     }
   delete this->Entries;
   this->Entries = newEntries;
-  
+
   // Compute fields from composites
   this->RePost();
 }
@@ -224,7 +224,7 @@ void cmCursesMainForm::RePost()
     std::vector<cmCursesCacheEntryComposite*>::iterator it;
     for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
       {
-      cmCacheManager::CacheIterator mit = 
+      cmCacheManager::CacheIterator mit =
         this->CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
       if (mit.IsAtEnd() ||
           (!this->AdvancedMode && mit.GetPropertyAsBool("ADVANCED")))
@@ -253,7 +253,7 @@ void cmCursesMainForm::RePost()
   std::vector<cmCursesCacheEntryComposite*>::iterator it;
   for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
     {
-    cmCacheManager::CacheIterator mit = 
+    cmCacheManager::CacheIterator mit =
       this->CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
     if (mit.IsAtEnd() ||
         (!this->AdvancedMode && mit.GetPropertyAsBool("ADVANCED")))
@@ -301,7 +301,7 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
     }
 
   // Wrong window size
-  if ( width < cmCursesMainForm::MIN_WIDTH  || 
+  if ( width < cmCursesMainForm::MIN_WIDTH  ||
        width < this->InitialWidth               ||
        height < cmCursesMainForm::MIN_HEIGHT )
     {
@@ -322,7 +322,7 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
     std::vector<cmCursesCacheEntryComposite*>::iterator it;
     for (it = this->Entries->begin(); it != this->Entries->end(); ++it)
       {
-      cmCacheManager::CacheIterator mit = 
+      cmCacheManager::CacheIterator mit =
         this->CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
       if (mit.IsAtEnd() ||
           (!this->AdvancedMode && mit.GetPropertyAsBool("ADVANCED")))
@@ -372,15 +372,15 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
   this->UpdateStatusBar();
   this->PrintKeys();
 
-  touchwin(stdscr); 
+  touchwin(stdscr);
   refresh();
 }
 
 void cmCursesMainForm::PrintKeys(int process /* = 0 */)
 {
   int x,y;
   getmaxyx(stdscr, y, x);
-  if ( x < cmCursesMainForm::MIN_WIDTH  || 
+  if ( x < cmCursesMainForm::MIN_WIDTH  ||
        x < this->InitialWidth               ||
        y < cmCursesMainForm::MIN_HEIGHT )
     {
@@ -399,7 +399,7 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
     {
     cw->PrintKeys();
     }
-  
+
 //    {
 //    }
 //  else
@@ -409,18 +409,18 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
   char thirdLine[512]="";
   if (process)
     {
-    sprintf(firstLine, 
-            "                                                               ");  
-    sprintf(secondLine, 
-            "                                                               ");  
-    sprintf(thirdLine, 
-            "                                                               ");  
+    sprintf(firstLine,
+            "                                                               ");
+    sprintf(secondLine,
+            "                                                               ");
+    sprintf(thirdLine,
+            "                                                               ");
     }
   else
     {
     if (this->OkToGenerate)
       {
-      sprintf(firstLine,  
+      sprintf(firstLine,
               "Press [c] to configure     Press [g] to generate and exit");
       }
     else
@@ -435,8 +435,8 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
       {
       sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently Off)");
       }
-    
-    sprintf(secondLine, 
+
+    sprintf(secondLine,
             "Press [h] for help         Press [q] to quit without generating");
     }
 
@@ -463,7 +463,7 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
 //    }
 
   pos_form_cursor(this->Form);
-  
+
 }
 
 // Print the key of the current entry and the CMake version
@@ -473,7 +473,7 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   int x,y;
   getmaxyx(stdscr, y, x);
   // If window size is too small, display error and return
-  if ( x < cmCursesMainForm::MIN_WIDTH  || 
+  if ( x < cmCursesMainForm::MIN_WIDTH  ||
        x < this->InitialWidth               ||
        y < cmCursesMainForm::MIN_HEIGHT )
     {
@@ -482,10 +482,10 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
     char fmt[] = "Window is too small. A size of at least %dx%d is required.";
     printw(fmt,
            (cmCursesMainForm::MIN_WIDTH < this->InitialWidth ?
-            this->InitialWidth : cmCursesMainForm::MIN_WIDTH), 
+            this->InitialWidth : cmCursesMainForm::MIN_WIDTH),
            cmCursesMainForm::MIN_HEIGHT);
-    touchwin(stdscr); 
-    wrefresh(stdscr); 
+    touchwin(stdscr);
+    wrefresh(stdscr);
     return;
     }
 
@@ -502,10 +502,10 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   if ( lbl )
     {
     curField = lbl->GetValue();
-    
+
     // Get the help string of the current entry
     // and add it to the help string
-    cmCacheManager::CacheIterator it = 
+    cmCacheManager::CacheIterator it =
       this->CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
     if (!it.IsAtEnd())
       {
@@ -549,9 +549,9 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
     if ( curFieldLen < width )
       {
       strcpy(bar, curField);
-      for(i=curFieldLen; i < width; ++i) 
-        { 
-        bar[i] = ' '; 
+      for(i=curFieldLen; i < width; ++i)
+        {
+        bar[i] = ' ';
         }
       }
     else
@@ -578,14 +578,14 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
       else
         {
         strcpy(bar+curFieldLen+2, help);
-        for(i=curFieldLen+helpLen+2; i < width; ++i) 
-          { 
-          bar[i] = ' '; 
+        for(i=curFieldLen+helpLen+2; i < width; ++i)
+          {
+          bar[i] = ' ';
           }
         }
       }
     }
-    
+
 
   bar[width] = '\0';
 
@@ -605,7 +605,7 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   attron(A_STANDOUT);
   char format[] = "%s";
   printw(format, bar);
-  attroff(A_STANDOUT);  
+  attroff(A_STANDOUT);
   curses_move(y-4,0);
   printw(version);
   pos_form_cursor(this->Form);
@@ -631,7 +631,7 @@ void cmCursesMainForm::UpdateProgress(const char *msg, float prog, void* vp)
   cm->UpdateStatusBar(cmsg);
   cm->PrintKeys(1);
   curses_move(1,1);
-  touchwin(stdscr); 
+  touchwin(stdscr);
   refresh();
 }
 
@@ -643,7 +643,7 @@ int cmCursesMainForm::Configure(int noconfigure)
   curses_move(1,1);
   this->UpdateStatusBar("Configuring, please wait...");
   this->PrintKeys(1);
-  touchwin(stdscr); 
+  touchwin(stdscr);
   refresh();
   this->CMakeInstance->SetProgressCallback(cmCursesMainForm::UpdateProgress, this);
 
@@ -652,7 +652,7 @@ int cmCursesMainForm::Configure(int noconfigure)
   this->CMakeInstance->GetCacheManager()->SaveCache(
     this->CMakeInstance->GetHomeOutputDirectory());
   this->LoadCache(0);
-  
+
   // Get rid of previous errors
   this->Errors = std::vector<std::string>();
 
@@ -674,8 +674,8 @@ int cmCursesMainForm::Configure(int noconfigure)
     }
   this->CMakeInstance->SetProgressCallback(0, 0);
 
-  keypad(stdscr,TRUE); /* Use key symbols as 
-                          KEY_DOWN*/ 
+  keypad(stdscr,TRUE); /* Use key symbols as
+                          KEY_DOWN*/
 
   if( retVal != 0 || !this->Errors.empty())
     {
@@ -705,10 +705,10 @@ int cmCursesMainForm::Configure(int noconfigure)
     CurrentForm = this;
     this->Render(1,1,xx,yy);
     }
-   
+
   this->InitializeUI();
   this->Render(1, 1, xi, yi);
-  
+
   return 0;
 }
 
@@ -731,8 +731,8 @@ int cmCursesMainForm::Generate()
   int retVal = this->CMakeInstance->Generate();
 
   this->CMakeInstance->SetProgressCallback(0, 0);
-  keypad(stdscr,TRUE); /* Use key symbols as 
-                          KEY_DOWN*/ 
+  keypad(stdscr,TRUE); /* Use key symbols as
+                          KEY_DOWN*/
 
   if( retVal != 0 || !this->Errors.empty())
     {
@@ -764,10 +764,10 @@ int cmCursesMainForm::Generate()
     CurrentForm = this;
     this->Render(1,1,xx,yy);
     }
-  
+
   this->InitializeUI();
   this->Render(1, 1, xi, yi);
-  
+
   return 0;
 }
 
@@ -798,11 +798,11 @@ void cmCursesMainForm::RemoveEntry(const char* value)
 
 // copy from the list box to the cache manager
 void cmCursesMainForm::FillCacheManagerFromUI()
-{   
+{
   size_t size = this->Entries->size();
   for(size_t i=0; i < size; i++)
     {
-    cmCacheManager::CacheIterator it = 
+    cmCacheManager::CacheIterator it =
       this->CMakeInstance->GetCacheManager()->GetCacheIterator(
         (*this->Entries)[i]->Key.c_str());
     if (!it.IsAtEnd())
@@ -872,14 +872,14 @@ void cmCursesMainForm::HandleInput()
       this->PrintKeys(1);
       curses_move(y-5,static_cast<unsigned int>(searchstr.size()));
       //curses_move(1,1);
-      touchwin(stdscr); 
+      touchwin(stdscr);
       refresh();
       }
     int key = getch();
 
     getmaxyx(stdscr, y, x);
     // If window too small, handle 'q' only
-    if ( x < cmCursesMainForm::MIN_WIDTH  || 
+    if ( x < cmCursesMainForm::MIN_WIDTH  ||
          y < cmCursesMainForm::MIN_HEIGHT )
       {
       // quit
@@ -948,7 +948,7 @@ void cmCursesMainForm::HandleInput()
       }
     if ((!currentWidget || !widgetHandled) && !this->SearchMode)
       {
-      // If the current widget does not want to handle input, 
+      // If the current widget does not want to handle input,
       // we handle it.
       sprintf(debugMessage, "Main form handling input, key: %d", key);
       cmCursesForm::LogMessage(debugMessage);
@@ -1028,7 +1028,7 @@ void cmCursesMainForm::HandleInput()
           this->Fields[findex-2]));
         const char* curField = lbl->GetValue();
         const char* helpString=0;
-        cmCacheManager::CacheIterator it = 
+        cmCacheManager::CacheIterator it =
           this->CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
         if (!it.IsAtEnd())
           {
@@ -1052,7 +1052,7 @@ void cmCursesMainForm::HandleInput()
         CurrentForm = msgs;
         msgs->Render(1,1,x,y);
         msgs->HandleInput();
-        CurrentForm = this; 
+        CurrentForm = this;
         this->Render(1,1,x,y);
         set_current_field(this->Form, cur);
         }
@@ -1137,7 +1137,7 @@ void cmCursesMainForm::HandleInput()
         // each entry consists of fields: label, isnew, value
         // therefore, the label field for the is findex-2
         // (findex always corresponds to the value field)
-        cmCursesWidget* lbl 
+        cmCursesWidget* lbl
           = reinterpret_cast<cmCursesWidget*>(
             field_userptr(this->Fields[findex-2]));
         if ( lbl )
@@ -1177,15 +1177,15 @@ void cmCursesMainForm::HandleInput()
         }
       }
 
-    touchwin(stdscr); 
-    wrefresh(stdscr); 
+    touchwin(stdscr);
+    wrefresh(stdscr);
     }
 }
 
 int cmCursesMainForm::LoadCache(const char *)
 
 {
-  int r = this->CMakeInstance->LoadCache(); 
+  int r = this->CMakeInstance->LoadCache();
   if(r < 0)
     {
     return r;
@@ -1194,7 +1194,7 @@ int cmCursesMainForm::LoadCache(const char *)
   this->CMakeInstance->PreLoadCMakeFiles();
   return r;
 }
-  
+
 void cmCursesMainForm::JumpToCacheEntry(const char* astr)
 {
   std::string str;
@@ -1247,7 +1247,7 @@ void cmCursesMainForm::JumpToCacheEntry(const char* astr)
     /*
     char buffer[1024];
     sprintf(buffer, "Line: %d != %d / %d\n", findex, idx, this->NumberOfVisibleEntries);
-    touchwin(stdscr); 
+    touchwin(stdscr);
     refresh();
     this->UpdateStatusBar( buffer );
     usleep(100000);
@@ -1262,7 +1262,7 @@ void cmCursesMainForm::JumpToCacheEntry(const char* astr)
 }
 
 
-const char* cmCursesMainForm::s_ConstHelpMessage = 
+const char* cmCursesMainForm::s_ConstHelpMessage =
 "CMake is used to configure and generate build files for software projects. "
 "The basic steps for configuring a project with ccmake are as follows:\n\n"
 "1. Run ccmake in the directory where you want the object and executable files to be placed (build directory). If the source directory is not the same as this build directory, you have to specify it as an argument on the command line.\n\n"