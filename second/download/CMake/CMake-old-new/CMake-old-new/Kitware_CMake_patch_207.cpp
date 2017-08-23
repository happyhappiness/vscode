@@ -80,12 +80,13 @@ void cmCursesLongMessageForm::UpdateStatusBar()
   sprintf(version+sideSpace, "%s", vertmp);
   version[width] = '\0';
 
+  char fmt_s[] = "%s";
   curses_move(y-4,0);
   attron(A_STANDOUT);
-  printw(bar);
+  printw(fmt_s, bar);
   attroff(A_STANDOUT);
   curses_move(y-3,0);
-  printw(version);
+  printw(fmt_s, version);
   pos_form_cursor(this->Form);
 }
 
@@ -101,8 +102,9 @@ void cmCursesLongMessageForm::PrintKeys()
   char firstLine[512];
   sprintf(firstLine,  "Press [e] to exit help");
 
+  char fmt_s[] = "%s";
   curses_move(y-2,0);
-  printw(firstLine);
+  printw(fmt_s, firstLine);
   pos_form_cursor(this->Form);
 
 }