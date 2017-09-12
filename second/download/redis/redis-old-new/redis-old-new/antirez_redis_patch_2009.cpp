@@ -169,6 +169,7 @@ static int cliReadBulkReply(int fd) {
 static int cliReadMultiBulkReply(int fd) {
     sds replylen = cliReadLine(fd);
     int elements, c = 1;
+    int retval = 0;
 
     if (replylen == NULL) return 1;
     elements = atoi(replylen);
@@ -182,10 +183,10 @@ static int cliReadMultiBulkReply(int fd) {
     }
     while(elements--) {
         printf("%d. ", c);
-        if (cliReadReply(fd)) return 1;
+        if (cliReadReply(fd)) retval = 1;
         c++;
     }
-    return 0;
+    return retval;
 }
 
 static int cliReadReply(int fd) {