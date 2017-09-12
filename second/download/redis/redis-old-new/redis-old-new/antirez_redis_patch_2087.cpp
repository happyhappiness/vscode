@@ -54,6 +54,7 @@ static struct config {
     long repeat;
     int dbnum;
     int interactive;
+    int shutdown;
     int monitor_mode;
     int pubsub_mode;
     int raw_output;
@@ -313,7 +314,10 @@ static int cliReadMultiBulkReply(int fd) {
 static int cliReadReply(int fd) {
     char type;
 
-    if (anetRead(fd,&type,1) <= 0) exit(1);
+    if (anetRead(fd,&type,1) <= 0) {
+        if (config.shutdown) return 0;
+        exit(1);
+    }
     switch(type) {
     case '-':
         printf("(error) ");
@@ -356,7 +360,6 @@ static int selectDb(int fd) {
 
 static int cliSendCommand(int argc, char **argv, int repeat) {
     struct redisCommand *rc = lookupCommand(argv[0]);
-    int shutdown = 0;
     int fd, j, retval = 0;
     sds cmd;
 
@@ -372,7 +375,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             return 1;
     }
 
-    if (!strcasecmp(rc->name,"shutdown")) shutdown = 1;
+    if (!strcasecmp(rc->name,"shutdown")) config.shutdown = 1;
     if (!strcasecmp(rc->name,"monitor")) config.monitor_mode = 1;
     if (!strcasecmp(rc->name,"subscribe") ||
         !strcasecmp(rc->name,"psubscribe")) config.pubsub_mode = 1;
@@ -410,8 +413,9 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         }
 
         retval = cliReadReply(fd);
+
         if (retval) {
-            return shutdown ? 0 : retval;
+            return retval;
         }
     }
     return 0;
@@ -594,6 +598,7 @@ int main(int argc, char **argv) {
     config.hostport = 6379;
     config.repeat = 1;
     config.dbnum = 0;
+    config.shutdown = 0;
     config.interactive = 0;
     config.monitor_mode = 0;
     config.pubsub_mode = 0;