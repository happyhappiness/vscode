@@ -226,6 +226,31 @@ static int cliReadSingleLineReply(int fd, int quiet) {
     return 0;
 }
 
+static void printStringRepr(char *s, int len) {
+    printf("\"");
+    while(len--) {
+        switch(*s) {
+        case '\\':
+        case '"':
+            printf("\\%c",*s);
+            break;
+        case '\n': printf("\\n"); break;
+        case '\r': printf("\\r"); break;
+        case '\t': printf("\\t"); break;
+        case '\a': printf("\\a"); break;
+        case '\b': printf("\\b"); break;
+        default:
+            if (isprint(*s))
+                printf("%c",*s);
+            else
+                printf("\\x%02x",(unsigned char)*s);
+            break;
+        }
+        s++;
+    }
+    printf("\"\n");
+}
+
 static int cliReadBulkReply(int fd) {
     sds replylen = cliReadLine(fd);
     char *reply, crlf[2];
@@ -241,12 +266,17 @@ static int cliReadBulkReply(int fd) {
     reply = zmalloc(bulklen);
     anetRead(fd,reply,bulklen);
     anetRead(fd,crlf,2);
-    if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
-        zfree(reply);
-        return 1;
+    if (!isatty(fileno(stdout))) {
+        if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
+            zfree(reply);
+            return 1;
+        }
+        if (reply[bulklen-1] != '\n') printf("\n");
+    } else {
+        /* If you are producing output for the standard output we want
+         * a more interesting output with quoted characters and so forth */
+        printStringRepr(reply,bulklen);
     }
-    if (isatty(fileno(stdout)) && reply[bulklen-1] != '\n')
-        printf("\n");
     zfree(reply);
     return 0;
 }