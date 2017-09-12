@@ -134,7 +134,7 @@ static void printStringRepr(char *s, int len) {
         }
         s++;
     }
-    printf("\"\n");
+    printf("\"");
 }
 
 static int cliReadBulkReply(int fd) {
@@ -152,7 +152,7 @@ static int cliReadBulkReply(int fd) {
     reply = zmalloc(bulklen);
     anetRead(fd,reply,bulklen);
     anetRead(fd,crlf,2);
-    if (config.raw_output || !config.interactive) {
+    if (config.raw_output) {
         if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
             zfree(reply);
             return 1;
@@ -161,6 +161,7 @@ static int cliReadBulkReply(int fd) {
         /* If you are producing output for the standard output we want
          * a more interesting output with quoted characters and so forth */
         printStringRepr(reply,bulklen);
+        printf("\n");
     }
     zfree(reply);
     return 0;