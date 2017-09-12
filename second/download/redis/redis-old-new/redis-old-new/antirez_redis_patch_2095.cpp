@@ -356,6 +356,7 @@ static int selectDb(int fd) {
 
 static int cliSendCommand(int argc, char **argv, int repeat) {
     struct redisCommand *rc = lookupCommand(argv[0]);
+    int shutdown = 0;
     int fd, j, retval = 0;
     sds cmd;
 
@@ -370,6 +371,8 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             fprintf(stderr,"Wrong number of arguments for '%s'\n",rc->name);
             return 1;
     }
+
+    if (!strcasecmp(rc->name,"shutdown")) shutdown = 1;
     if (!strcasecmp(rc->name,"monitor")) config.monitor_mode = 1;
     if (!strcasecmp(rc->name,"subscribe") ||
         !strcasecmp(rc->name,"psubscribe")) config.pubsub_mode = 1;
@@ -408,7 +411,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
 
         retval = cliReadReply(fd);
         if (retval) {
-            return retval;
+            return shutdown ? 0 : retval;
         }
     }
     return 0;