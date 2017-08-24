@@ -241,9 +241,9 @@ void cmCursesMainForm::PrintKeys()
   sprintf(firstLine,  "C)onfigure             G)enerate and Exit");
   sprintf(secondLine, "Q)uit                  H)elp");
 
-  move(y-2,0);
+  curses_move(y-2,0);
   printw(firstLine);
-  move(y-1,0);
+  curses_move(y-1,0);
   printw(secondLine);
   pos_form_cursor(m_Form);
   
@@ -258,7 +258,7 @@ void cmCursesMainForm::UpdateStatusBar()
   if ( x < cmCursesMainForm::MIN_WIDTH  || 
        y < cmCursesMainForm::MIN_HEIGHT )
     {
-    move(0,0);
+    curses_move(0,0);
     printw("Window is too small. A size of at least %dx%d is required.",
 	   cmCursesMainForm::MIN_WIDTH, cmCursesMainForm::MIN_HEIGHT);
     touchwin(m_Window); 
@@ -310,7 +310,7 @@ void cmCursesMainForm::UpdateStatusBar()
     bar[cmCursesMainForm::MAX_WIDTH-1] = '\0';
     }
 
-  move(y-3,0);
+  curses_move(y-3,0);
   attron(A_STANDOUT);
   printw(bar);
   attroff(A_STANDOUT);  