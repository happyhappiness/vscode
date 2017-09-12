@@ -96,7 +96,7 @@ static sds cliReadLine(int fd) {
         ssize_t ret;
 
         ret = read(fd,&c,1);
-        if (ret == -1) {
+        if (ret <= 0) {
             sdsfree(line);
             return NULL;
         } else if ((ret == 0) || (c == '\n')) {
@@ -282,7 +282,8 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     while(repeat--) {
         anetWrite(fd,cmd,sdslen(cmd));
         while (config.monitor_mode) {
-            cliReadSingleLineReply(fd,0);
+            if (cliReadSingleLineReply(fd,0)) exit(1);
+            printf("\n");
         }
 
         if (config.pubsub_mode) {