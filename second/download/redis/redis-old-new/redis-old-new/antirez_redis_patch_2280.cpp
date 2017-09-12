@@ -49,6 +49,7 @@
 static struct config {
     char *hostip;
     int hostport;
+    long repeat;
 } config;
 
 struct redisCommand {
@@ -255,7 +256,7 @@ static int cliReadReply(int fd) {
 static int cliSendCommand(int argc, char **argv) {
     struct redisCommand *rc = lookupCommand(argv[0]);
     int fd, j, retval = 0;
-    sds cmd = sdsempty();
+    sds cmd;
 
     if (!rc) {
         fprintf(stderr,"Unknown command '%s'\n",argv[0]);
@@ -269,35 +270,39 @@ static int cliSendCommand(int argc, char **argv) {
     }
     if ((fd = cliConnect()) == -1) return 1;
 
-    /* Build the command to send */
-    if (rc->flags & REDIS_CMD_MULTIBULK) {
-        cmd = sdscatprintf(cmd,"*%d\r\n",argc);
-        for (j = 0; j < argc; j++) {
-            cmd = sdscatprintf(cmd,"$%d\r\n",sdslen(argv[j]));
-            cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
-            cmd = sdscatlen(cmd,"\r\n",2);
-        }
-    } else {
-        for (j = 0; j < argc; j++) {
-            if (j != 0) cmd = sdscat(cmd," ");
-            if (j == argc-1 && rc->flags & REDIS_CMD_BULK) {
-                cmd = sdscatprintf(cmd,"%d",sdslen(argv[j]));
-            } else {
+    while(config.repeat--) {
+        /* Build the command to send */
+        cmd = sdsempty();
+        if (rc->flags & REDIS_CMD_MULTIBULK) {
+            cmd = sdscatprintf(cmd,"*%d\r\n",argc);
+            for (j = 0; j < argc; j++) {
+                cmd = sdscatprintf(cmd,"$%d\r\n",sdslen(argv[j]));
                 cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
+                cmd = sdscatlen(cmd,"\r\n",2);
+            }
+        } else {
+            for (j = 0; j < argc; j++) {
+                if (j != 0) cmd = sdscat(cmd," ");
+                if (j == argc-1 && rc->flags & REDIS_CMD_BULK) {
+                    cmd = sdscatprintf(cmd,"%d",sdslen(argv[j]));
+                } else {
+                    cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
+                }
+            }
+            cmd = sdscat(cmd,"\r\n");
+            if (rc->flags & REDIS_CMD_BULK) {
+                cmd = sdscatlen(cmd,argv[argc-1],sdslen(argv[argc-1]));
+                cmd = sdscatlen(cmd,"\r\n",2);
             }
         }
-        cmd = sdscat(cmd,"\r\n");
-        if (rc->flags & REDIS_CMD_BULK) {
-            cmd = sdscatlen(cmd,argv[argc-1],sdslen(argv[argc-1]));
-            cmd = sdscatlen(cmd,"\r\n",2);
+        anetWrite(fd,cmd,sdslen(cmd));
+        sdsfree(cmd);
+        retval = cliReadReply(fd);
+        if (retval) {
+            close(fd);
+            return retval;
         }
     }
-    anetWrite(fd,cmd,sdslen(cmd));
-    retval = cliReadReply(fd);
-    if (retval) {
-        close(fd);
-        return retval;
-    }
     close(fd);
     return 0;
 }
@@ -319,6 +324,9 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
             config.hostport = atoi(argv[i+1]);
             i++;
+        } else if (!strcmp(argv[i],"-r") && !lastarg) {
+            config.repeat = strtoll(argv[i+1],NULL,10);
+            i++;
         } else {
             break;
         }
@@ -350,6 +358,7 @@ int main(int argc, char **argv) {
 
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
+    config.repeat = 1;
 
     firstarg = parseOptions(argc,argv);
     argc -= firstarg;
@@ -361,11 +370,12 @@ int main(int argc, char **argv) {
         argvcopy[j] = sdsnew(argv[j]);
 
     if (argc < 1) {
-        fprintf(stderr, "usage: redis-cli [-h host] [-p port] cmd arg1 arg2 arg3 ... argN\n");
-        fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] cmd arg1 arg2 ... arg(N-1)\n");
+        fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] cmd arg1 arg2 arg3 ... argN\n");
+        fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] -r [repeat_times] cmd arg1 arg2 ... arg(N-1)\n");
         fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
         fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
         fprintf(stderr, "example: redis-cli get my_passwd\n");
+        fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
         exit(1);
     }
 