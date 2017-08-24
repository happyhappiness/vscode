@@ -34,7 +34,7 @@ inline int ctrl(int z)
 } 
 
 cmCursesMainForm::cmCursesMainForm(std::vector<std::string> const& args,
-				   int initWidth) :
+                                   int initWidth) :
   m_Args(args), m_InitialWidth(initWidth)
 {
   m_NumberOfPages = 0;
@@ -119,7 +119,7 @@ void cmCursesMainForm::InitializeUI()
       !i.IsAtEnd(); i.Next())
     {
     if ( i.GetType() != cmCacheManager::INTERNAL &&
-	 i.GetType() != cmCacheManager::STATIC  &&
+         i.GetType() != cmCacheManager::STATIC  &&
          i.GetType() != cmCacheManager::UNINITIALIZED)
       {
       ++count;
@@ -148,19 +148,19 @@ void cmCursesMainForm::InitializeUI()
       {
       const char* key = i.GetName();
       if ( i.GetType() == cmCacheManager::INTERNAL || 
-	   i.GetType() == cmCacheManager::STATIC ||
+           i.GetType() == cmCacheManager::STATIC ||
            i.GetType() == cmCacheManager::UNINITIALIZED )
-	{
-	continue;
-	}
+        {
+        continue;
+        }
 
       if (!this->LookForCacheEntry(key))
-	{
-	newEntries->push_back(new cmCursesCacheEntryComposite(key, i,
-							      true, 30,
-							      entrywidth));
-	m_OkToGenerate = false;
-	}
+        {
+        newEntries->push_back(new cmCursesCacheEntryComposite(key, i,
+                                                              true, 30,
+                                                              entrywidth));
+        m_OkToGenerate = false;
+        }
       }
 
     // then add entries which are old
@@ -170,18 +170,18 @@ void cmCursesMainForm::InitializeUI()
       {
       const char* key = i.GetName();
       if ( i.GetType() == cmCacheManager::INTERNAL || 
-	   i.GetType() == cmCacheManager::STATIC ||
+           i.GetType() == cmCacheManager::STATIC ||
            i.GetType() == cmCacheManager::UNINITIALIZED )
-	{
-	continue;
-	}
+        {
+        continue;
+        }
 
       if (this->LookForCacheEntry(key))
-	{
-	newEntries->push_back(new cmCursesCacheEntryComposite(key, i,
-							      false, 30,
-							      entrywidth));
-	}
+        {
+        newEntries->push_back(new cmCursesCacheEntryComposite(key, i,
+                                                              false, 30,
+                                                              entrywidth));
+        }
       }
     }
   
@@ -228,9 +228,9 @@ void cmCursesMainForm::RePost()
       cmCacheManager::CacheIterator mit = 
         this->m_CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
       if (mit.IsAtEnd() || !m_AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
-	{
-	continue;
-	}
+        {
+        continue;
+        }
       m_NumberOfVisibleEntries++;
       }
     }
@@ -270,8 +270,8 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
       (field_userptr(currentField));
     // If in edit mode, get out of it
     if ( cw->GetType() == cmCacheManager::STRING ||
-	 cw->GetType() == cmCacheManager::PATH   ||
-	 cw->GetType() == cmCacheManager::FILEPATH )
+         cw->GetType() == cmCacheManager::PATH   ||
+         cw->GetType() == cmCacheManager::FILEPATH )
       {
       cmCursesStringWidget* sw = static_cast<cmCursesStringWidget*>(cw);
       sw->SetInEdit(false);
@@ -308,8 +308,8 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
         this->m_CMakeInstance->GetCacheManager()->GetCacheIterator((*it)->GetValue());
       if (mit.IsAtEnd() || !m_AdvancedMode && mit.GetPropertyAsBool("ADVANCED"))
         {
-	continue;
-	}
+        continue;
+        }
       m_NumberOfVisibleEntries++;
       }
     }
@@ -439,21 +439,21 @@ void cmCursesMainForm::UpdateStatusBar()
     curses_move(0,0);
     char fmt[] = "Window is too small. A size of at least %dx%d is required.";
     printw(fmt,
-	   (cmCursesMainForm::MIN_WIDTH < m_InitialWidth ?
-	    m_InitialWidth : cmCursesMainForm::MIN_WIDTH), 
-	   cmCursesMainForm::MIN_HEIGHT);
+           (cmCursesMainForm::MIN_WIDTH < m_InitialWidth ?
+            m_InitialWidth : cmCursesMainForm::MIN_WIDTH), 
+           cmCursesMainForm::MIN_HEIGHT);
     touchwin(stdscr); 
     wrefresh(stdscr); 
     return;
     }
 
   // Get the key of the current entry
   FIELD* cur = current_field(m_Form);
-  int index = field_index(cur);
+  int findex = field_index(cur);
   cmCursesWidget* lbl = 0;
-  if ( index >= 0 )
+  if ( findex >= 0 )
     {
-    lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(m_Fields[index-2]));
+    lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(m_Fields[findex-2]));
     }
   char help[128] = "";
   const char* curField = "";
@@ -531,7 +531,7 @@ void cmCursesMainForm::UpdateStatusBar()
   char version[cmCursesMainForm::MAX_WIDTH];
   char vertmp[128];
   sprintf(vertmp,"CMake Version %d.%d - %s", cmake::GetMajorVersion(),
-	  cmake::GetMinorVersion(),cmake::GetReleaseVersion());
+          cmake::GetMinorVersion(),cmake::GetReleaseVersion());
   int sideSpace = (width-strlen(vertmp));
   for(i=0; i<sideSpace; i++) { version[i] = ' '; }
   sprintf(version+sideSpace, "%s", vertmp);
@@ -550,8 +550,8 @@ void cmCursesMainForm::UpdateStatusBar()
 int cmCursesMainForm::Configure()
 {
 
-  int x,y;
-  getmaxyx(stdscr, y, x);
+  int xi,yi;
+  getmaxyx(stdscr, yi, xi);
 
   curses_clear();
   curses_move(1,1);
@@ -578,7 +578,7 @@ int cmCursesMainForm::Configure()
   noecho(); /* Echo off */ 
   cbreak(); /* nl- or cr not needed */ 
   keypad(stdscr,TRUE); /* Use key symbols as 
-			  KEY_DOWN*/ 
+                          KEY_DOWN*/ 
 
   if( retVal != 0 || !m_Errors.empty())
     {
@@ -589,12 +589,12 @@ int cmCursesMainForm::Configure()
       }
     // reset error condition
     cmSystemTools::ResetErrorOccuredFlag();
-    int x,y;
-    getmaxyx(stdscr, y, x);
+    int xx,yy;
+    getmaxyx(stdscr, yy, xx);
     cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
-								"Errors occurred during the last pass.");
+                                                                "Errors occurred during the last pass.");
     CurrentForm = msgs;
-    msgs->Render(1,1,x,y);
+    msgs->Render(1,1,xx,yy);
     msgs->HandleInput();
     // If they typed the wrong source directory, we report
     // an error and exit
@@ -603,19 +603,19 @@ int cmCursesMainForm::Configure()
       return retVal;
       }
     CurrentForm = this;
-    this->Render(1,1,x,y);
+    this->Render(1,1,xx,yy);
     }
    
   this->InitializeUI();
-  this->Render(1, 1, x, y);
+  this->Render(1, 1, xi, yi);
   
   return 0;
 }
 
 int cmCursesMainForm::Generate()
 {
-  int x,y;
-  getmaxyx(stdscr, y, x);
+  int xi,yi;
+  getmaxyx(stdscr, yi, xi);
 
   curses_clear();
   curses_move(1,1);
@@ -634,7 +634,7 @@ int cmCursesMainForm::Generate()
   noecho(); /* Echo off */ 
   cbreak(); /* nl- or cr not needed */ 
   keypad(stdscr,TRUE); /* Use key symbols as 
-			  KEY_DOWN*/ 
+                          KEY_DOWN*/ 
 
   if( retVal != 0 || !m_Errors.empty())
     {
@@ -645,12 +645,12 @@ int cmCursesMainForm::Generate()
       }
     // reset error condition
     cmSystemTools::ResetErrorOccuredFlag();
-    int x,y;
-    getmaxyx(stdscr, y, x);
+    int xx,yy;
+    getmaxyx(stdscr, yy, xx);
     cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
-								"Errors occurred during the last pass.");
+                                                                "Errors occurred during the last pass.");
     CurrentForm = msgs;
-    msgs->Render(1,1,x,y);
+    msgs->Render(1,1,xx,yy);
     msgs->HandleInput();
     // If they typed the wrong source directory, we report
     // an error and exit
@@ -659,11 +659,11 @@ int cmCursesMainForm::Generate()
       return retVal;
       }
     CurrentForm = this;
-    this->Render(1,1,x,y);
+    this->Render(1,1,xx,yy);
     }
   
   this->InitializeUI();
-  this->Render(1, 1, x, y);
+  this->Render(1, 1, xi, yi);
   
   return 0;
 }
@@ -702,19 +702,19 @@ void cmCursesMainForm::FillCacheManagerFromUI()
     {
     cmCacheManager::CacheIterator it = 
       this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(
-	(*m_Entries)[i]->m_Key.c_str());
+        (*m_Entries)[i]->m_Key.c_str());
     if (!it.IsAtEnd())
       {
       tmpString = (*m_Entries)[i]->m_Entry->GetValue();
 
       // Remove trailing spaces, convert path to unix slashes
       std::string tmpSubString = 
-	tmpString.substr(0,tmpString.find_last_not_of(" ")+1);
+        tmpString.substr(0,tmpString.find_last_not_of(" ")+1);
       if ( it.GetType() == cmCacheManager::PATH || 
-	   it.GetType() == cmCacheManager::FILEPATH )
-	{
-	cmSystemTools::ConvertToUnixSlashes(tmpSubString);
-	}
+           it.GetType() == cmCacheManager::FILEPATH )
+        {
+        cmSystemTools::ConvertToUnixSlashes(tmpSubString);
+        }
       it.SetValue(tmpSubString.c_str());
       }
     }
@@ -743,17 +743,17 @@ void cmCursesMainForm::HandleInput()
     getmaxyx(stdscr, y, x);
     // If window too small, handle 'q' only
     if ( x < cmCursesMainForm::MIN_WIDTH  || 
-	 y < cmCursesMainForm::MIN_HEIGHT )
+         y < cmCursesMainForm::MIN_HEIGHT )
       {
       // quit
       if ( key == 'q' )
-	{
-	break;
-	}
+        {
+        break;
+        }
       else
-	{
-	continue;
-	}
+        {
+        continue;
+        }
       }
 
     currentField = current_field(m_Form);
@@ -781,207 +781,207 @@ void cmCursesMainForm::HandleInput()
       cmCursesForm::LogMessage(debugMessage);
       // quit
       if ( key == 'q' )
-	{
-	break;
-	}
+        {
+        break;
+        }
       // if not end of page, next field otherwise next page
       // each entry consists of fields: label, isnew, value
       // therefore, the label field for the prev. entry is index-5
       // and the label field for the next entry is index+1
       // (index always corresponds to the value field)
       else if ( key == KEY_DOWN || key == ctrl('n') )
-	{
-	FIELD* cur = current_field(m_Form);
-	int index = field_index(cur);
-	if ( index == 3*m_NumberOfVisibleEntries-1 )
-	  {
-	  continue;
-	  }
-	if (new_page(m_Fields[index+1]))
-	  {
-	  form_driver(m_Form, REQ_NEXT_PAGE);
-	  }
-	else
-	  {
-	  form_driver(m_Form, REQ_NEXT_FIELD);
-	  }
-	}
+        {
+        FIELD* cur = current_field(m_Form);
+        int findex = field_index(cur);
+        if ( findex == 3*m_NumberOfVisibleEntries-1 )
+          {
+          continue;
+          }
+        if (new_page(m_Fields[findex+1]))
+          {
+          form_driver(m_Form, REQ_NEXT_PAGE);
+          }
+        else
+          {
+          form_driver(m_Form, REQ_NEXT_FIELD);
+          }
+        }
       // if not beginning of page, previous field, otherwise previous page
       // each entry consists of fields: label, isnew, value
       // therefore, the label field for the prev. entry is index-5
       // and the label field for the next entry is index+1
       // (index always corresponds to the value field)
       else if ( key == KEY_UP || key == ctrl('p') )
-	{
-	FIELD* cur = current_field(m_Form);
-	int index = field_index(cur);
-	if ( index == 2 )
-	  {
-	  continue;
-	  }
-	if ( new_page(m_Fields[index-2]) )
-	  {
-	  form_driver(m_Form, REQ_PREV_PAGE);
-	  set_current_field(m_Form, m_Fields[index-3]);
-	  }
-	else
-	  {
-	  form_driver(m_Form, REQ_PREV_FIELD);
-	  }
-	}
+        {
+        FIELD* cur = current_field(m_Form);
+        int findex = field_index(cur);
+        if ( findex == 2 )
+          {
+          continue;
+          }
+        if ( new_page(m_Fields[findex-2]) )
+          {
+          form_driver(m_Form, REQ_PREV_PAGE);
+          set_current_field(m_Form, m_Fields[findex-3]);
+          }
+        else
+          {
+          form_driver(m_Form, REQ_PREV_FIELD);
+          }
+        }
       // pg down
       else if ( key == KEY_NPAGE || key == ctrl('d') )
-	{
-	form_driver(m_Form, REQ_NEXT_PAGE);
-	}
+        {
+        form_driver(m_Form, REQ_NEXT_PAGE);
+        }
       // pg up
       else if ( key == KEY_PPAGE || key == ctrl('u') )
-	{
-	form_driver(m_Form, REQ_PREV_PAGE);
-	}
+        {
+        form_driver(m_Form, REQ_PREV_PAGE);
+        }
       // configure
       else if ( key == 'c' )
-	{
-	this->Configure();
-	}
+        {
+        this->Configure();
+        }
       // display help
       else if ( key == 'h' )
-	{
-	getmaxyx(stdscr, y, x);
-
-	FIELD* cur = current_field(m_Form);
-	int index = field_index(cur);
-	cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
-	  m_Fields[index-2]));
-	const char* curField = lbl->GetValue();
-	const char* helpString=0;
-	cmCacheManager::CacheIterator it = 
-	  this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
-	if (!it.IsAtEnd())
-	  {
-	  helpString = it.GetProperty("HELPSTRING");
-	  }
-	if (helpString)
-	  {
-	  char* message = new char[strlen(curField)+strlen(helpString)
-				  +strlen("Current option is: \n Help string for this option is: \n")+10];
-	  sprintf(message,"Current option is: %s\nHelp string for this option is: %s\n", curField, helpString);
-	  m_HelpMessage[1] = message;
-	  delete[] message;
-	  }
-	else
-	  {
-	  m_HelpMessage[1] = "";
-	  }
-
-	cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_HelpMessage,
-								    "Help.");
-	CurrentForm = msgs;
-	msgs->Render(1,1,x,y);
-	msgs->HandleInput();
-	CurrentForm = this;
-	this->Render(1,1,x,y);
-	}
+        {
+        getmaxyx(stdscr, y, x);
+
+        FIELD* cur = current_field(m_Form);
+        int findex = field_index(cur);
+        cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
+          m_Fields[findex-2]));
+        const char* curField = lbl->GetValue();
+        const char* helpString=0;
+        cmCacheManager::CacheIterator it = 
+          this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(curField);
+        if (!it.IsAtEnd())
+          {
+          helpString = it.GetProperty("HELPSTRING");
+          }
+        if (helpString)
+          {
+          char* message = new char[strlen(curField)+strlen(helpString)
+                                  +strlen("Current option is: \n Help string for this option is: \n")+10];
+          sprintf(message,"Current option is: %s\nHelp string for this option is: %s\n", curField, helpString);
+          m_HelpMessage[1] = message;
+          delete[] message;
+          }
+        else
+          {
+          m_HelpMessage[1] = "";
+          }
+
+        cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_HelpMessage,
+                                                                    "Help.");
+        CurrentForm = msgs;
+        msgs->Render(1,1,x,y);
+        msgs->HandleInput();
+        CurrentForm = this;
+        this->Render(1,1,x,y);
+        }
       // display last errors
       else if ( key == 'l' )
-	{
-	getmaxyx(stdscr, y, x);
-	cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
-								    "Errors occurred during the last pass.");
-	CurrentForm = msgs;
-	msgs->Render(1,1,x,y);
-	msgs->HandleInput();
-	CurrentForm = this;
-	this->Render(1,1,x,y);
-	}
+        {
+        getmaxyx(stdscr, y, x);
+        cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
+                                                                    "Errors occurred during the last pass.");
+        CurrentForm = msgs;
+        msgs->Render(1,1,x,y);
+        msgs->HandleInput();
+        CurrentForm = this;
+        this->Render(1,1,x,y);
+        }
       // switch advanced on/off
       else if ( key == 't' )
-	{
-	if (m_AdvancedMode)
-	  {
-	  m_AdvancedMode = false;
-	  }
-	else
-	  {
-	  m_AdvancedMode = true;
-	  }
-	getmaxyx(stdscr, y, x);
-	this->RePost();
-	this->Render(1, 1, x, y);
-	}
+        {
+        if (m_AdvancedMode)
+          {
+          m_AdvancedMode = false;
+          }
+        else
+          {
+          m_AdvancedMode = true;
+          }
+        getmaxyx(stdscr, y, x);
+        this->RePost();
+        this->Render(1, 1, x, y);
+        }
       // generate and exit
       else if ( key == 'g' )
-	{
-	if ( m_OkToGenerate )
-	  {
-	  this->Generate();
-	  break;
-	  }
-	}
+        {
+        if ( m_OkToGenerate )
+          {
+          this->Generate();
+          break;
+          }
+        }
       // delete cache entry
       else if ( key == 'd' )
-	{
+        {
         m_OkToGenerate = false;
-	FIELD* cur = current_field(m_Form);
-	int index = field_index(cur);
-
-	// make the next or prev. current field after deletion
-	// each entry consists of fields: label, isnew, value
-	// therefore, the label field for the prev. entry is index-5
-	// and the label field for the next entry is index+1
-	// (index always corresponds to the value field)
-	FIELD* nextCur;
-	if ( index == 2 )
-	  {
-	  nextCur=0;
-	  }
-	else if ( index == 3*m_NumberOfVisibleEntries-1 )
-	  {
-	  nextCur = m_Fields[index-5];
-	  }
-	else
-	  {
-	  nextCur = m_Fields[index+1];
-	  }
-
-	// Get the label widget
-	// each entry consists of fields: label, isnew, value
-	// therefore, the label field for the is index-2
-	// (index always corresponds to the value field)
-	cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
-	  m_Fields[index-2]));
-	this->m_CMakeInstance->GetCacheManager()->RemoveCacheEntry(lbl->GetValue());
-
-	std::string nextVal;
-	if (nextCur)
-	  {
-	  nextVal = (reinterpret_cast<cmCursesWidget*>(field_userptr(nextCur))->GetValue());
-	  }
-
-	getmaxyx(stdscr, y, x);
-	this->RemoveEntry(lbl->GetValue());
-	this->RePost();
-	this->Render(1, 1, x, y);
-
-	if (nextCur)
-	  {
-	  // make the next or prev. current field after deletion
-	  nextCur = 0;
-	  std::vector<cmCursesCacheEntryComposite*>::iterator it;
-	  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
-	    {
-	    if (nextVal == (*it)->m_Key)
-	      {
-	      nextCur = (*it)->m_Entry->m_Field;
-	      }
-	    }
-	  
-	  if (nextCur)
-	    {
-	    set_current_field(m_Form, nextCur);
-	    }
-	  }
-	}
+        FIELD* cur = current_field(m_Form);
+        int findex = field_index(cur);
+
+        // make the next or prev. current field after deletion
+        // each entry consists of fields: label, isnew, value
+        // therefore, the label field for the prev. entry is findex-5
+        // and the label field for the next entry is findex+1
+        // (findex always corresponds to the value field)
+        FIELD* nextCur;
+        if ( findex == 2 )
+          {
+          nextCur=0;
+          }
+        else if ( findex == 3*m_NumberOfVisibleEntries-1 )
+          {
+          nextCur = m_Fields[findex-5];
+          }
+        else
+          {
+          nextCur = m_Fields[findex+1];
+          }
+
+        // Get the label widget
+        // each entry consists of fields: label, isnew, value
+        // therefore, the label field for the is findex-2
+        // (findex always corresponds to the value field)
+        cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
+          m_Fields[findex-2]));
+        this->m_CMakeInstance->GetCacheManager()->RemoveCacheEntry(lbl->GetValue());
+
+        std::string nextVal;
+        if (nextCur)
+          {
+          nextVal = (reinterpret_cast<cmCursesWidget*>(field_userptr(nextCur))->GetValue());
+          }
+
+        getmaxyx(stdscr, y, x);
+        this->RemoveEntry(lbl->GetValue());
+        this->RePost();
+        this->Render(1, 1, x, y);
+
+        if (nextCur)
+          {
+          // make the next or prev. current field after deletion
+          nextCur = 0;
+          std::vector<cmCursesCacheEntryComposite*>::iterator it;
+          for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
+            {
+            if (nextVal == (*it)->m_Key)
+              {
+              nextCur = (*it)->m_Entry->m_Field;
+              }
+            }
+          
+          if (nextCur)
+            {
+            set_current_field(m_Form, nextCur);
+            }
+          }
+        }
       }
 
     touchwin(stdscr); 