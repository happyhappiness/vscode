@@ -28,7 +28,7 @@ void cmakewizard::AskUser(const char* key,
   printf("Current Value: %s\n", iter.GetValue());
   printf("New Value (Enter to keep current value): ");
   char buffer[4096];
-  if(!fgets(buffer, sizeof(buffer)-1, stdin))
+  if(!fgets(buffer, static_cast<int>(sizeof(buffer) - 1), stdin))
     {
     buffer[0] = 0;
     }
@@ -67,7 +67,7 @@ bool cmakewizard::AskAdvanced()
 {
   printf("Would you like to see advanced options? [No]:");
   char buffer[4096];
-  if(!fgets(buffer, sizeof(buffer)-1, stdin))
+  if(!fgets(buffer, static_cast<int>(sizeof(buffer) - 1), stdin))
     {
     buffer[0] = 0;
     }