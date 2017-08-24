@@ -29,7 +29,7 @@ void cmakewizard::AskUser(const char* key,
   printf("New Value (Enter to keep current value): ");
   char buffer[4096];
   buffer[0] = 0;
-  fgets(buffer, sizeof(buffer)-1, stdin);
+  (void) fgets(buffer, sizeof(buffer)-1, stdin);
 
   if(strlen(buffer) > 0)
     {
@@ -66,7 +66,7 @@ bool cmakewizard::AskAdvanced()
   printf("Would you like to see advanced options? [No]:");
   char buffer[4096];
   buffer[0] = 0;
-  fgets(buffer, sizeof(buffer)-1, stdin);
+  (void) fgets(buffer, sizeof(buffer)-1, stdin);
   if(buffer[0])
     {
     if(buffer[0] == 'y' || buffer[0] == 'Y')