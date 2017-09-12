@@ -96,7 +96,7 @@ static sds cliReadLine(int fd) {
         ssize_t ret;
 
         ret = read(fd,&c,1);
-        if (ret == -1) {
+        if (ret <= 0) {
             sdsfree(line);
             return NULL;
         } else if ((ret == 0) || (c == '\n')) {
@@ -251,12 +251,32 @@ static int selectDb(int fd) {
     return 0;
 }
 
+static void showInteractiveHelp(void) {
+    printf(
+    "\n"
+    "Welcome to redis-cli " REDIS_VERSION "!\n"
+    "Just type any valid Redis command to see a pretty printed output.\n"
+    "\n"
+    "It is possible to quote strings, like in:\n"
+    "  set \"my key\" \"some string \\xff\\n\"\n"
+    "\n"
+    "You can find a list of valid Redis commands at\n"
+    "  http://code.google.com/p/redis/wiki/CommandReference\n"
+    "\n"
+    "Note: redis-cli supports line editing, use up/down arrows for history."
+    "\n\n");
+}
+
 static int cliSendCommand(int argc, char **argv, int repeat) {
     char *command = argv[0];
     int fd, j, retval = 0;
     sds cmd;
 
     config.raw_output = !strcasecmp(command,"info");
+    if (!strcasecmp(command,"help")) {
+        showInteractiveHelp();
+        return 0;
+    }
     if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
     if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
     if (!strcasecmp(command,"subscribe") ||
@@ -282,7 +302,8 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     while(repeat--) {
         anetWrite(fd,cmd,sdslen(cmd));
         while (config.monitor_mode) {
-            cliReadSingleLineReply(fd,0);
+            if (cliReadSingleLineReply(fd,0)) exit(1);
+            printf("\n");
         }
 
         if (config.pubsub_mode) {
@@ -477,10 +498,16 @@ int main(int argc, char **argv) {
 
     if (config.auth != NULL) {
         char *authargv[2];
+        int dbnum = config.dbnum;
 
+        /* We need to save the real configured database number and set it to
+         * zero here, otherwise cliSendCommand() will try to perform the
+         * SELECT command before the authentication, and it will fail. */
+        config.dbnum = 0;
         authargv[0] = "AUTH";
         authargv[1] = config.auth;
         cliSendCommand(2, convertToSds(2, authargv), 1);
+        config.dbnum = dbnum; /* restore the right DB number */
     }
 
     /* Start interactive mode when no command is provided */