@@ -191,7 +191,7 @@ static int cliReadBulkReply(int fd) {
     bulklen = atoi(replylen);
     if (bulklen == -1) {
         sdsfree(replylen);
-        printf("(nil)");
+        printf("(nil)\n");
         return 0;
     }
     reply = zmalloc(bulklen);