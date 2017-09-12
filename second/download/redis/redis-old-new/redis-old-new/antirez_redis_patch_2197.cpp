@@ -138,6 +138,9 @@ static struct redisCommand cmdTable[] = {
     {"mset",-3,REDIS_CMD_MULTIBULK},
     {"msetnx",-3,REDIS_CMD_MULTIBULK},
     {"monitor",1,REDIS_CMD_INLINE},
+    {"multi",1,REDIS_CMD_INLINE},
+    {"exec",1,REDIS_CMD_MULTIBULK},
+    {"discard",1,REDIS_CMD_INLINE},
     {NULL,0,0}
 };
 
@@ -155,14 +158,16 @@ static struct redisCommand *lookupCommand(char *name) {
 
 static int cliConnect(void) {
     char err[ANET_ERR_LEN];
-    int fd;
+    static int fd = ANET_ERR;
 
-    fd = anetTcpConnect(err,config.hostip,config.hostport);
     if (fd == ANET_ERR) {
-        fprintf(stderr,"Connect: %s\n",err);
-        return -1;
+        fd = anetTcpConnect(err,config.hostip,config.hostport);
+        if (fd == ANET_ERR) {
+            fprintf(stderr, "Could not connect to Redis at %s:%d: %s", config.hostip, config.hostport, err);
+            return -1;
+        }
+        anetTcpNoDelay(NULL,fd);
     }
-    anetTcpNoDelay(NULL,fd);
     return fd;
 }
 
@@ -282,7 +287,6 @@ static int selectDb(int fd) {
     if (type <= 0 || type != '+') return 1;
     retval = cliReadSingleLineReply(fd,1);
     if (retval) {
-        close(fd);
         return retval;
     }
     return 0;
@@ -350,11 +354,9 @@ static int cliSendCommand(int argc, char **argv) {
 
         retval = cliReadReply(fd);
         if (retval) {
-            close(fd);
             return retval;
         }
     }
-    close(fd);
     return 0;
 }
 