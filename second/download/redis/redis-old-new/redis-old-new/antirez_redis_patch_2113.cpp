@@ -58,13 +58,9 @@ int readString(FILE *fp, char** target) {
     len += 2;
     *target = (char*)malloc(len);
     if (!readBytes(fp,*target,len)) {
-        free(*target);
-        *target = NULL;
         return 0;
     }
     if (!consumeNewline(*target+len-2)) {
-        free(*target);
-        *target = NULL;
         return 0;
     }
     (*target)[len-2] = '\0';
@@ -82,14 +78,10 @@ long process(FILE *fp) {
 
     while(1) {
         if (!multi) pos = ftell(fp);
-        if (!readArgc(fp, &argc)) {
-            break;
-        }
+        if (!readArgc(fp, &argc)) break;
 
         for (i = 0; i < argc; i++) {
-            if (!readString(fp,&str)) {
-                break;
-            }
+            if (!readString(fp,&str)) break;
             if (i == 0) {
                 if (strcasecmp(str, "multi") == 0) {
                     if (multi++) {
@@ -106,7 +98,7 @@ long process(FILE *fp) {
             free(str);
         }
 
-        /* Check if loop was finished */
+        /* Stop if the loop did not finish */
         if (i < argc) {
             if (str) free(str);
             break;
@@ -116,11 +108,9 @@ long process(FILE *fp) {
     if (feof(fp) && multi && strlen(error) == 0) {
         ERROR("Reached EOF before reading EXEC for MULTI");
     }
-
     if (strlen(error) > 0) {
         printf("%s\n", error);
     }
-
     return pos;
 }
 