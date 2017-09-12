@@ -134,6 +134,7 @@ static struct redisCommand cmdTable[] = {
     {"debug",-2,REDIS_CMD_INLINE},
     {"mset",-3,REDIS_CMD_MULTIBULK},
     {"msetnx",-3,REDIS_CMD_MULTIBULK},
+    {"monitor",1,REDIS_CMD_INLINE},
     {NULL,0,0}
 };
 
@@ -188,6 +189,7 @@ static int cliReadSingleLineReply(int fd, int quiet) {
     if (reply == NULL) return 1;
     if (!quiet)
         printf("%s\n", reply);
+    sdsfree(reply);
     return 0;
 }
 
@@ -287,6 +289,7 @@ static int selectDb(int fd)
 static int cliSendCommand(int argc, char **argv) {
     struct redisCommand *rc = lookupCommand(argv[0]);
     int fd, j, retval = 0;
+    int read_forever = 0;
     sds cmd;
 
     if (!rc) {
@@ -299,6 +302,7 @@ static int cliSendCommand(int argc, char **argv) {
             fprintf(stderr,"Wrong number of arguments for '%s'\n",rc->name);
             return 1;
     }
+    if (!strcasecmp(rc->name,"monitor")) read_forever = 1;
     if ((fd = cliConnect()) == -1) return 1;
 
     /* Select db number */
@@ -337,6 +341,11 @@ static int cliSendCommand(int argc, char **argv) {
         }
         anetWrite(fd,cmd,sdslen(cmd));
         sdsfree(cmd);
+
+        while (read_forever) {
+            cliReadSingleLineReply(fd,0);
+        }
+
         retval = cliReadReply(fd);
         if (retval) {
             close(fd);