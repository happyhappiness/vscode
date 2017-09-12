@@ -54,6 +54,8 @@ static struct config {
     long repeat;
     int dbnum;
     int interactive;
+    int monitor_mode;
+    int pubsub_mode;
     char *auth;
 } config;
 
@@ -165,6 +167,8 @@ static struct redisCommand cmdTable[] = {
     {"config",-2,REDIS_CMD_BULK},
     {"subscribe",-2,REDIS_CMD_INLINE},
     {"unsubscribe",-1,REDIS_CMD_INLINE},
+    {"psubscribe",-2,REDIS_CMD_INLINE},
+    {"punsubscribe",-1,REDIS_CMD_INLINE},
     {"publish",3,REDIS_CMD_BULK},
     {NULL,0,0}
 };
@@ -349,7 +353,6 @@ static int selectDb(int fd) {
 static int cliSendCommand(int argc, char **argv, int repeat) {
     struct redisCommand *rc = lookupCommand(argv[0]);
     int fd, j, retval = 0;
-    int read_forever = 0;
     sds cmd;
 
     if (!rc) {
@@ -362,7 +365,9 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             fprintf(stderr,"Wrong number of arguments for '%s'\n",rc->name);
             return 1;
     }
-    if (!strcasecmp(rc->name,"monitor")) read_forever = 1;
+    if (!strcasecmp(rc->name,"monitor")) config.monitor_mode = 1;
+    if (!strcasecmp(rc->name,"subscribe") ||
+        !strcasecmp(rc->name,"psubscribe")) config.pubsub_mode = 1;
     if ((fd = cliConnect()) == -1) return 1;
 
     /* Select db number */
@@ -402,10 +407,18 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         anetWrite(fd,cmd,sdslen(cmd));
         sdsfree(cmd);
 
-        while (read_forever) {
+        while (config.monitor_mode) {
             cliReadSingleLineReply(fd,0);
         }
 
+        if (config.pubsub_mode) {
+            printf("Reading messages... (press Ctrl-c to quit)\n");
+            while (1) {
+                cliReadReply(fd);
+                printf("\n");
+            }
+        }
+
         retval = cliReadReply(fd);
         if (retval) {
             return retval;
@@ -592,6 +605,8 @@ int main(int argc, char **argv) {
     config.repeat = 1;
     config.dbnum = 0;
     config.interactive = 0;
+    config.monitor_mode = 0;
+    config.pubsub_mode = 0;
     config.auth = NULL;
 
     firstarg = parseOptions(argc,argv);