@@ -89,7 +89,7 @@ void cmCursesLongMessageForm::PrintKeys()
     return;
     }
   char firstLine[512];
-  sprintf(firstLine,  "O)k");
+  sprintf(firstLine,  "Press [e] to exit help");
 
   curses_move(y-2,0);
   printw(firstLine);
@@ -166,7 +166,7 @@ void cmCursesLongMessageForm::HandleInput()
     cmCursesForm::LogMessage(debugMessage);
 
     // quit
-    if ( key == 'o' )
+    if ( key == 'o' || key == 'e' )
       {
       break;
       }