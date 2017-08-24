@@ -28,7 +28,7 @@ void cmakewizard::AskUser(const char* key,
   printf("Current Value: %s\n", iter.GetValue());
   printf("New Value (Enter to keep current value): ");
   char buffer[4096];
-  if(!fgets(buffer, sizeof(buffer)-1, stdin))
+  if(!fgets(buffer, static_cast<int>(sizeof(buffer) - 1), stdin))
     {
     buffer[0] = 0;
     }
@@ -67,16 +67,13 @@ bool cmakewizard::AskAdvanced()
 {
   printf("Would you like to see advanced options? [No]:");
   char buffer[4096];
-  if(!fgets(buffer, sizeof(buffer)-1, stdin))
+  if(!fgets(buffer, static_cast<int>(sizeof(buffer) - 1), stdin))
     {
     buffer[0] = 0;
     }
-  if(buffer[0])
+  else if(buffer[0] == 'y' || buffer[0] == 'Y')
     {
-    if(buffer[0] == 'y' || buffer[0] == 'Y')
-      {
-      return true;
-      }
+    return true;
     }
   return false;
 }