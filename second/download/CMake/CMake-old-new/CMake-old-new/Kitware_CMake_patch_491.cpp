@@ -28,8 +28,10 @@ void cmakewizard::AskUser(const char* key,
   printf("Current Value: %s\n", iter.GetValue());
   printf("New Value (Enter to keep current value): ");
   char buffer[4096];
-  buffer[0] = 0;
-  fgets(buffer, sizeof(buffer)-1, stdin);
+  if(!fgets(buffer, sizeof(buffer)-1, stdin))
+    {
+    buffer[0] = 0;
+    }
 
   if(strlen(buffer) > 0)
     {
@@ -65,8 +67,10 @@ bool cmakewizard::AskAdvanced()
 {
   printf("Would you like to see advanced options? [No]:");
   char buffer[4096];
-  buffer[0] = 0;
-  fgets(buffer, sizeof(buffer)-1, stdin);
+  if(!fgets(buffer, sizeof(buffer)-1, stdin))
+    {
+    buffer[0] = 0;
+    }
   if(buffer[0])
     {
     if(buffer[0] == 'y' || buffer[0] == 'Y')