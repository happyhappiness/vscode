@@ -47,6 +47,12 @@ cmCursesMainForm::cmCursesMainForm(std::vector<std::string> const& args,
   m_HelpMessage.push_back("");
   m_HelpMessage.push_back(s_ConstHelpMessage);
   m_CMakeInstance = new cmake;
+
+  // create the arguments for the cmake object
+  std::string whereCMake = cmSystemTools::GetProgramPath(m_Args[0].c_str());
+  whereCMake += "/cmake";
+  m_Args[0] = whereCMake;
+  m_CMakeInstance->SetArgs(m_Args);
 }
 
 cmCursesMainForm::~cmCursesMainForm()
@@ -362,19 +368,23 @@ void cmCursesMainForm::PrintKeys()
     cw = reinterpret_cast<cmCursesWidget*>(field_userptr(currentField));
     }
 
-  if (cw && cw->PrintKeys())
+  if (cw)
     {
+    cw->PrintKeys();
     }
-  else
-    {
+  
+//    {
+//    }
+//  else
+//    {
     char firstLine[512], secondLine[512], thirdLine[512];
     if (m_OkToGenerate)
       {
       sprintf(firstLine,  "Press [c] to configure     Press [g] to generate and exit");
       }
     else
       {
-      sprintf(firstLine,  "Press [c] to configure");
+      sprintf(firstLine,  "Press [c] to configure                                   ");
       }
     if (m_AdvancedMode)
       {
@@ -404,7 +414,7 @@ void cmCursesMainForm::PrintKeys()
       curses_move(0,65-strlen(firstLine)-1);
       printw(firstLine);
       }
-    }
+//    }
 
   pos_form_cursor(m_Form);
   
@@ -504,8 +514,8 @@ void cmCursesMainForm::UpdateStatusBar()
   // We want to display this on the right
   char version[cmCursesMainForm::MAX_WIDTH];
   char vertmp[128];
-  sprintf(vertmp,"CMake Version %d.%d - %s", cmMakefile::GetMajorVersion(),
-	  cmMakefile::GetMinorVersion(),cmMakefile::GetReleaseVersion());
+  sprintf(vertmp,"CMake Version %d.%d - %s", cmake::GetMajorVersion(),
+	  cmake::GetMinorVersion(),cmake::GetReleaseVersion());
   int sideSpace = (width-strlen(vertmp));
   for(i=0; i<sideSpace; i++) { version[i] = ' '; }
   sprintf(version+sideSpace, "%s", vertmp);
@@ -521,7 +531,7 @@ void cmCursesMainForm::UpdateStatusBar()
   pos_form_cursor(m_Form);
 }
 
-int cmCursesMainForm::RunCMake(bool generateMakefiles)
+int cmCursesMainForm::Configure()
 {
 
   int x,y;
@@ -532,33 +542,21 @@ int cmCursesMainForm::RunCMake(bool generateMakefiles)
   touchwin(stdscr);
   refresh();
   endwin();
-  std::cerr << "Running CMake, please wait...\n\r";
+  std::cerr << "Configuring, please wait...\n\r";
 
-  // free the old cmake and create a new one here
-  if (this->m_CMakeInstance)
-    {
-    delete this->m_CMakeInstance;
-    this->m_CMakeInstance = 0;
-    }
-  this->m_CMakeInstance = new cmake;
 
   // always save the current gui values to disk
   this->FillCacheManagerFromUI();
   this->m_CMakeInstance->GetCacheManager()->SaveCache(
     cmSystemTools::GetCurrentWorkingDirectory().c_str());
 
-  // create the arguments for the cmake object
-  std::string whereCMake = cmSystemTools::GetProgramPath(m_Args[0].c_str());
-  whereCMake += "/cmake";
-
-  m_Args[0] = whereCMake;
-
+  
   // Get rid of previous errors
   m_Errors = std::vector<std::string>();
 
   // run the generate process
   m_OkToGenerate = true;
-  int retVal = this->m_CMakeInstance->Generate(m_Args, generateMakefiles);
+  int retVal = this->m_CMakeInstance->Configure(m_Args[0].c_str(), &m_Args);
 
   initscr(); /* Initialization */ 
   noecho(); /* Echo off */ 
@@ -591,14 +589,71 @@ int cmCursesMainForm::RunCMake(bool generateMakefiles)
     CurrentForm = this;
     this->Render(1,1,x,y);
     }
-
    
   this->InitializeUI();
   this->Render(1, 1, x, y);
   
   return 0;
 }
 
+int cmCursesMainForm::Generate()
+{
+  m_CMakeInstance->Generate();
+  
+  int x,y;
+  getmaxyx(stdscr, y, x);
+
+  curses_clear();
+  curses_move(1,1);
+  touchwin(stdscr);
+  refresh();
+  endwin();
+  std::cerr << "Generating, please wait...\n\r";
+
+  // Get rid of previous errors
+  m_Errors = std::vector<std::string>();
+
+  // run the generate process
+  int retVal = this->m_CMakeInstance->Generate();
+
+  initscr(); /* Initialization */ 
+  noecho(); /* Echo off */ 
+  cbreak(); /* nl- or cr not needed */ 
+  keypad(stdscr,TRUE); /* Use key symbols as 
+			  KEY_DOWN*/ 
+
+  if( retVal != 0 || !m_Errors.empty())
+    {
+    // see if there was an error
+    if(cmSystemTools::GetErrorOccuredFlag())
+      {
+      m_OkToGenerate = false;
+      }
+    // reset error condition
+    cmSystemTools::ResetErrorOccuredFlag();
+    int x,y;
+    getmaxyx(stdscr, y, x);
+    cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
+								"Errors which during last pass.");
+    CurrentForm = msgs;
+    msgs->Render(1,1,x,y);
+    msgs->HandleInput();
+    // If they typed the wrong source directory, we report
+    // an error and exit
+    if ( retVal == -2 )
+      {
+      return retVal;
+      }
+    CurrentForm = this;
+    this->Render(1,1,x,y);
+    }
+  
+  this->InitializeUI();
+  this->Render(1, 1, x, y);
+  
+  return 0;
+}
+
 void cmCursesMainForm::AddError(const char* message, const char*)
 {
   m_Errors.push_back(message);
@@ -693,7 +748,19 @@ void cmCursesMainForm::HandleInput()
       currentField));
 
     // Ask the current widget if it wants to handle input
-    if (!currentWidget || !currentWidget->HandleInput(key, this, stdscr))
+    bool widgetHandled;
+    
+    if (currentWidget)
+      {
+      widgetHandled = currentWidget->HandleInput(key, this, stdscr);
+      if (widgetHandled)
+        {
+        m_OkToGenerate = false;
+        this->UpdateStatusBar();
+        this->PrintKeys();
+        }
+      }
+    if (!currentWidget || !widgetHandled)
       {
       // If the current widget does not want to handle input, 
       // we handle it.
@@ -762,7 +829,7 @@ void cmCursesMainForm::HandleInput()
       // configure
       else if ( key == 'c' )
 	{
-	this->RunCMake(false);
+	this->Configure();
 	}
       // display help
       else if ( key == 'h' )
@@ -834,13 +901,14 @@ void cmCursesMainForm::HandleInput()
 	{
 	if ( m_OkToGenerate )
 	  {
-	  this->RunCMake(true);
+	  this->Generate();
 	  break;
 	  }
 	}
       // delete cache entry
       else if ( key == 'd' )
 	{
+        m_OkToGenerate = false;
 	FIELD* cur = current_field(m_Form);
 	int index = field_index(cur);
 