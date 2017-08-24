@@ -421,7 +421,7 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
     if (this->OkToGenerate)
       {
       sprintf(firstLine,
-              "Press [c] to configure     Press [g] to generate and exit");
+              "Press [c] to configure       Press [g] to generate and exit");
       }
     else
       {
@@ -437,7 +437,8 @@ void cmCursesMainForm::PrintKeys(int process /* = 0 */)
       }
 
     sprintf(secondLine,
-            "Press [h] for help         Press [q] to quit without generating");
+            "Press [h] for help           "
+            "Press [q] to quit without generating");
     }
 
   curses_move(y-4,0);