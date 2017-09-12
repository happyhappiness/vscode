@@ -239,6 +239,7 @@ static int cliReadReply(int fd) {
         return 1;
     case '+':
     case ':':
+        printf("(integer) ");
         return cliReadSingleLineReply(fd);
     case '$':
         return cliReadBulkReply(fd);