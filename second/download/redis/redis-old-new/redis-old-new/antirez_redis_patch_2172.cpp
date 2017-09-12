@@ -52,6 +52,7 @@ static struct config {
     long repeat;
     int dbnum;
     int interactive;
+    char *authpw;
 } config;
 
 struct redisCommand {
@@ -61,6 +62,7 @@ struct redisCommand {
 };
 
 static struct redisCommand cmdTable[] = {
+    {"auth",2,REDIS_CMD_INLINE},
     {"get",2,REDIS_CMD_INLINE},
     {"set",3,REDIS_CMD_BULK},
     {"setnx",3,REDIS_CMD_BULK},
@@ -305,6 +307,32 @@ static int selectDb(int fd) {
     return 0;
 }
 
+static int cliLogin(int fd)
+{
+    int retval = 1;
+    sds cmd;
+    char type;
+    if (config.authpw != "")
+    {
+        cmd = sdsempty();
+        cmd = sdscatprintf(cmd,"AUTH %s\r\n",config.authpw);
+        anetWrite(fd,cmd,sdslen(cmd));
+        anetRead(fd,&type,1);
+        if (type == '+') 
+        {
+            retval = 0;
+        }
+        int ret2 = cliReadSingleLineReply(fd,1);
+        if (ret2)
+        {
+            close(fd);
+        }
+    } else {
+        retval = 0;
+    }
+    return retval;
+}
+
 static int cliSendCommand(int argc, char **argv) {
     struct redisCommand *rc = lookupCommand(argv[0]);
     int fd, j, retval = 0;
@@ -331,6 +359,13 @@ static int cliSendCommand(int argc, char **argv) {
         return 1;
     }
 
+    /* Login if necessary */
+    retval = cliLogin(fd);
+    if (retval) {
+        fprintf(stderr,"Authentication failed\n");
+        return 1;
+    }
+
     while(config.repeat--) {
         /* Build the command to send */
         cmd = sdsempty();
@@ -398,6 +433,9 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-n") && !lastarg) {
             config.dbnum = atoi(argv[i+1]);
             i++;
+        } else if (!strcmp(argv[i],"-a") && !lastarg) {
+            config.authpw = argv[i+1];
+            i++;
         } else if (!strcmp(argv[i],"-i")) {
             config.interactive = 1;
         } else {
@@ -425,8 +463,8 @@ static sds readArgFromStdin(void) {
 }
 
 static void usage() {
-    fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] [-i] cmd arg1 arg2 arg3 ... argN\n");
-    fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
+    fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] [-i] cmd arg1 arg2 arg3 ... argN\n");
+    fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-a authpw] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
     fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
     fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
     fprintf(stderr, "example: redis-cli get my_passwd\n");