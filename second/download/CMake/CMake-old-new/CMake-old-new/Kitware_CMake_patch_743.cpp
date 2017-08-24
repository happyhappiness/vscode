@@ -353,7 +353,7 @@ void cmCursesMainForm::Render(int left, int top, int width, int height)
   refresh();
 }
 
-void cmCursesMainForm::PrintKeys()
+void cmCursesMainForm::PrintKeys(int process /* = 0 */)
 {
   int x,y;
   getmaxyx(stdscr, y, x);
@@ -381,10 +381,24 @@ void cmCursesMainForm::PrintKeys()
 //    }
 //  else
 //    {
-    char firstLine[512], secondLine[512], thirdLine[512];
+  char firstLine[512]="";
+  char secondLine[512]="";
+  char thirdLine[512]="";
+  if (process)
+    {
+    sprintf(firstLine, 
+            "                                                               ");  
+    sprintf(secondLine, 
+            "                                                               ");  
+    sprintf(thirdLine, 
+            "                                                               ");  
+    }
+  else
+    {
     if (m_OkToGenerate)
       {
-      sprintf(firstLine,  "Press [c] to configure     Press [g] to generate and exit");
+      sprintf(firstLine,  
+              "Press [c] to configure     Press [g] to generate and exit");
       }
     else
       {
@@ -399,25 +413,30 @@ void cmCursesMainForm::PrintKeys()
       sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently Off)");
       }
     
-    sprintf(secondLine, "Press [h] for help         Press [q] to quit without generating");
+    sprintf(secondLine, 
+            "Press [h] for help         Press [q] to quit without generating");
+    }
 
+  curses_move(y-4,0);
+  char *fmt = "Press [enter] to edit option";
+  if ( process )
+    {
+    fmt = "                           ";
+    }
+  printw(fmt);
+  curses_move(y-3,0);
+  printw(firstLine);
+  curses_move(y-2,0);
+  printw(secondLine);
+  curses_move(y-1,0);
+  printw(thirdLine);
 
-    curses_move(y-4,0);
-    char fmt[] = "Press [enter] to edit option";
-    printw(fmt);
-    curses_move(y-3,0);
+  if (cw)
+    {
+    sprintf(firstLine, "Page %d of %d", cw->GetPage(), m_NumberOfPages);
+    curses_move(0,65-strlen(firstLine)-1);
     printw(firstLine);
-    curses_move(y-2,0);
-    printw(secondLine);
-    curses_move(y-1,0);
-    printw(thirdLine);
-
-    if (cw)
-      {
-      sprintf(firstLine, "Page %d of %d", cw->GetPage(), m_NumberOfPages);
-      curses_move(0,65-strlen(firstLine)-1);
-      printw(firstLine);
-      }
+    }
 //    }
 
   pos_form_cursor(m_Form);
@@ -426,7 +445,7 @@ void cmCursesMainForm::PrintKeys()
 
 // Print the key of the current entry and the CMake version
 // on the status bar. Designed for a width of 80 chars.
-void cmCursesMainForm::UpdateStatusBar()
+void cmCursesMainForm::UpdateStatusBar(const char* message)
 {
   int x,y;
   getmaxyx(stdscr, y, x);
@@ -500,32 +519,54 @@ void cmCursesMainForm::UpdateStatusBar()
     width = cmCursesMainForm::MAX_WIDTH;
     }
 
-  if (curFieldLen >= width)
+  if ( message )
     {
-    strncpy(bar, curField, width);
-    }
+    curField = message;
+    curFieldLen = strlen(message);
+    if ( curFieldLen < width )
+      {
+      strcpy(bar, curField);
+      for(i=curFieldLen; i < width; ++i) 
+        { 
+        bar[i] = ' '; 
+        }
+      }
+    else
+      {
+      strncpy(bar, curField, width);
+      }
+   }
   else
     {
-    strcpy(bar, curField);
-    bar[curFieldLen] = ':';
-    bar[curFieldLen+1] = ' ';
-    if (curFieldLen + helpLen + 2 >= width)
+    if (curFieldLen >= width)
       {
-      strncpy(bar+curFieldLen+2, help, width
-              - curFieldLen - 2);
+      strncpy(bar, curField, width);
       }
     else
       {
-      strcpy(bar+curFieldLen+2, help);
-      for(i=curFieldLen+helpLen+2; i < width; ++i) 
-        { 
-        bar[i] = ' '; 
+      strcpy(bar, curField);
+      bar[curFieldLen] = ':';
+      bar[curFieldLen+1] = ' ';
+      if (curFieldLen + helpLen + 2 >= width)
+        {
+        strncpy(bar+curFieldLen+2, help, width
+                - curFieldLen - 2);
+        }
+      else
+        {
+        strcpy(bar+curFieldLen+2, help);
+        for(i=curFieldLen+helpLen+2; i < width; ++i) 
+          { 
+          bar[i] = ' '; 
+          }
         }
       }
     }
+    
 
   bar[width] = '\0';
 
+
   // Display CMake version info on the next line
   // We want to display this on the right
   char version[cmCursesMainForm::MAX_WIDTH];
@@ -540,33 +581,56 @@ void cmCursesMainForm::UpdateStatusBar()
   // Now print both lines
   curses_move(y-5,0);
   attron(A_STANDOUT);
-  printw(bar);
+  printw("%s", bar);
   attroff(A_STANDOUT);  
   curses_move(y-4,0);
   printw(version);
   pos_form_cursor(m_Form);
 }
 
-void cmCursesMainForm::UpdateProgress(const char *msg, float prog, void*)
+void cmCursesMainForm::UpdateProgressOld(const char *msg, float prog, void*)
 {
   if ( prog < 0 )
     {
     std::cout << "-- " << msg << std::endl;
     }
 }
 
+void cmCursesMainForm::UpdateProgress(const char *msg, float prog, void* vp)
+{
+  cmCursesMainForm* cm = static_cast<cmCursesMainForm*>(vp);
+  if ( !cm )
+    {
+    return;
+    }
+  char tmp[1024];
+  const char *cmsg = tmp;
+  if ( prog >= 0 )
+    {
+    sprintf(tmp, "%s %i%%",msg,(int)(100*prog));
+    }
+  else
+    {
+    cmsg = msg;
+    }
+  cm->UpdateStatusBar(cmsg);
+  cm->PrintKeys(1);
+  curses_move(1,1);
+  touchwin(stdscr); 
+  refresh();
+}
+
 int cmCursesMainForm::Configure()
 {
 
   int xi,yi;
   getmaxyx(stdscr, yi, xi);
 
-  curses_clear();
   curses_move(1,1);
-  touchwin(stdscr);
+  this->UpdateStatusBar("Configuring, please wait...");
+  this->PrintKeys(1);
+  touchwin(stdscr); 
   refresh();
-  endwin();
-  std::cerr << "Configuring, please wait...\n\r";
   this->m_CMakeInstance->SetProgressCallback(cmCursesMainForm::UpdateProgress, this);
 
   // always save the current gui values to disk
@@ -583,9 +647,6 @@ int cmCursesMainForm::Configure()
   int retVal = this->m_CMakeInstance->Configure();
   this->m_CMakeInstance->SetProgressCallback(0, 0);
 
-  initscr(); /* Initialization */ 
-  noecho(); /* Echo off */ 
-  cbreak(); /* nl- or cr not needed */ 
   keypad(stdscr,TRUE); /* Use key symbols as 
                           KEY_DOWN*/ 
 
@@ -626,12 +687,11 @@ int cmCursesMainForm::Generate()
   int xi,yi;
   getmaxyx(stdscr, yi, xi);
 
-  curses_clear();
   curses_move(1,1);
+  this->UpdateStatusBar("Generating, please wait...");
+  this->PrintKeys(1);
   touchwin(stdscr);
   refresh();
-  endwin();
-  std::cerr << "Generating, please wait...\n\r";
   this->m_CMakeInstance->SetProgressCallback(cmCursesMainForm::UpdateProgress, this);
 
   // Get rid of previous errors
@@ -641,9 +701,6 @@ int cmCursesMainForm::Generate()
   int retVal = this->m_CMakeInstance->Generate();
 
   this->m_CMakeInstance->SetProgressCallback(0, 0);
-  initscr(); /* Initialization */ 
-  noecho(); /* Echo off */ 
-  cbreak(); /* nl- or cr not needed */ 
   keypad(stdscr,TRUE); /* Use key symbols as 
                           KEY_DOWN*/ 
 