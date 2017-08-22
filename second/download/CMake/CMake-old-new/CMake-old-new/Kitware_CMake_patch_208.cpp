@@ -451,24 +451,25 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
     }
 
   curses_move(y-4,0);
+  char fmt_s[] = "%s";
   char fmt[512] = "Press [enter] to edit option";
   if ( process )
     {
     strcpy(fmt, "                           ");
     }
-  printw(fmt);
+  printw(fmt_s, fmt);
   curses_move(y-3,0);
-  printw(firstLine);
+  printw(fmt_s, firstLine);
   curses_move(y-2,0);
-  printw(secondLine);
+  printw(fmt_s, secondLine);
   curses_move(y-1,0);
-  printw(thirdLine);
+  printw(fmt_s, thirdLine);
 
   if (cw)
     {
     sprintf(firstLine, "Page %d of %d", cw->GetPage(), this->NumberOfPages);
     curses_move(0,65-static_cast<unsigned int>(strlen(firstLine))-1);
-    printw(firstLine);
+    printw(fmt_s, firstLine);
     }
 //    }
 
@@ -612,13 +613,13 @@ void cmCursesMainForm::UpdateStatusBar(const char* message)
   version[width] = '\0';
 
   // Now print both lines
+  char fmt_s[] = "%s";
   curses_move(y-5,0);
   attron(A_STANDOUT);
-  char format[] = "%s";
-  printw(format, bar);
+  printw(fmt_s, bar);
   attroff(A_STANDOUT);
   curses_move(y-4,0);
-  printw(version);
+  printw(fmt_s, version);
   pos_form_cursor(this->Form);
 }
 