@@ -42,6 +42,7 @@
 
 #define REDIS_CMD_INLINE 1
 #define REDIS_CMD_BULK 2
+#define REDIS_CMD_MULTIBULK 3
 
 #define REDIS_NOTUSED(V) ((void) V)
 
@@ -113,6 +114,8 @@ static struct redisCommand cmdTable[] = {
     {"ttl",2,REDIS_CMD_INLINE},
     {"slaveof",3,REDIS_CMD_INLINE},
     {"debug",-2,REDIS_CMD_INLINE},
+    {"mset",-3,REDIS_CMD_MULTIBULK},
+    {"msetnx",-3,REDIS_CMD_MULTIBULK},
     {NULL,0,0}
 };
 
@@ -255,18 +258,27 @@ static int cliSendCommand(int argc, char **argv) {
     if ((fd = cliConnect()) == -1) return 1;
 
     /* Build the command to send */
-    for (j = 0; j < argc; j++) {
-        if (j != 0) cmd = sdscat(cmd," ");
-        if (j == argc-1 && rc->flags & REDIS_CMD_BULK) {
-            cmd = sdscatprintf(cmd,"%d",sdslen(argv[j]));
-        } else {
+    if (rc->flags & REDIS_CMD_MULTIBULK) {
+        cmd = sdscatprintf(cmd,"*%d\r\n",argc);
+        for (j = 0; j < argc; j++) {
+            cmd = sdscatprintf(cmd,"$%d\r\n",sdslen(argv[j]));
             cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
+            cmd = sdscatlen(cmd,"\r\n",2);
+        }
+    } else {
+        for (j = 0; j < argc; j++) {
+            if (j != 0) cmd = sdscat(cmd," ");
+            if (j == argc-1 && rc->flags & REDIS_CMD_BULK) {
+                cmd = sdscatprintf(cmd,"%d",sdslen(argv[j]));
+            } else {
+                cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
+            }
         }
-    }
-    cmd = sdscat(cmd,"\r\n");
-    if (rc->flags & REDIS_CMD_BULK) {
-        cmd = sdscatlen(cmd,argv[argc-1],sdslen(argv[argc-1]));
         cmd = sdscat(cmd,"\r\n");
+        if (rc->flags & REDIS_CMD_BULK) {
+            cmd = sdscatlen(cmd,argv[argc-1],sdslen(argv[argc-1]));
+            cmd = sdscatlen(cmd,"\r\n",2);
+        }
     }
     anetWrite(fd,cmd,sdslen(cmd));
     retval = cliReadReply(fd);