@@ -52,7 +52,7 @@ static struct config {
     long repeat;
     int dbnum;
     int interactive;
-    char *authpw;
+    char *auth;
 } config;
 
 struct redisCommand {
@@ -307,27 +307,6 @@ static int selectDb(int fd) {
     return 0;
 }
 
-static int cliLogin(int fd)
-{
-    int retval = 1;
-    sds cmd;
-    char type;
-    if (config.authpw[0] != '\0') {
-        cmd = sdsempty();
-        cmd = sdscatprintf(cmd,"AUTH %s\r\n",config.authpw);
-        anetWrite(fd,cmd,sdslen(cmd));
-        anetRead(fd,&type,1);
-        if (type == '+') 
-            retval = 0;
-        int ret2 = cliReadSingleLineReply(fd,1);
-        if (ret2)
-            close(fd);
-    } else {
-        retval = 0;
-    }
-    return retval;
-}
-
 static int cliSendCommand(int argc, char **argv) {
     struct redisCommand *rc = lookupCommand(argv[0]);
     int fd, j, retval = 0;
@@ -354,13 +333,6 @@ static int cliSendCommand(int argc, char **argv) {
         return 1;
     }
 
-    /* Login if necessary */
-    retval = cliLogin(fd);
-    if (retval) {
-        fprintf(stderr,"Authentication failed\n");
-        return 1;
-    }
-
     while(config.repeat--) {
         /* Build the command to send */
         cmd = sdsempty();
@@ -429,7 +401,7 @@ static int parseOptions(int argc, char **argv) {
             config.dbnum = atoi(argv[i+1]);
             i++;
         } else if (!strcmp(argv[i],"-a") && !lastarg) {
-            config.authpw = argv[i+1];
+            config.auth = argv[i+1];
             i++;
         } else if (!strcmp(argv[i],"-i")) {
             config.interactive = 1;
@@ -497,6 +469,14 @@ static void repl() {
     char *line = buffer;
     char **ap, *args[max];
 
+    if (config.auth != NULL) {
+        char *authargv[2];
+
+        authargv[0] = "AUTH";
+        authargv[1] = config.auth;
+        cliSendCommand(2, convertToSds(2, authargv));
+    }
+
     while (prompt(line, size)) {
         argc = 0;
 
@@ -528,6 +508,7 @@ int main(int argc, char **argv) {
     config.repeat = 1;
     config.dbnum = 0;
     config.interactive = 0;
+    config.auth = NULL;
 
     firstarg = parseOptions(argc,argv);
     argc -= firstarg;