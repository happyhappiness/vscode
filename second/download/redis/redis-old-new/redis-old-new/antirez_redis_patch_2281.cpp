@@ -238,6 +238,7 @@ static int cliReadReply(int fd) {
         cliReadSingleLineReply(fd);
         return 1;
     case '+':
+        return cliReadSingleLineReply(fd);
     case ':':
         printf("(integer) ");
         return cliReadSingleLineReply(fd);