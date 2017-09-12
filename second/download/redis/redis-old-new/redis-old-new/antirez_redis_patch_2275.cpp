@@ -50,6 +50,7 @@ static struct config {
     char *hostip;
     int hostport;
     long repeat;
+    int dbnum;
 } config;
 
 struct redisCommand {
@@ -175,11 +176,12 @@ static sds cliReadLine(int fd) {
     return sdstrim(line,"\r\n");
 }
 
-static int cliReadSingleLineReply(int fd) {
+static int cliReadSingleLineReply(int fd, int quiet) {
     sds reply = cliReadLine(fd);
 
     if (reply == NULL) return 1;
-    printf("%s\n", reply);
+    if (!quiet)
+        printf("%s\n", reply);
     return 0;
 }
 
@@ -237,13 +239,13 @@ static int cliReadReply(int fd) {
     switch(type) {
     case '-':
         printf("(error) ");
-        cliReadSingleLineReply(fd);
+        cliReadSingleLineReply(fd,0);
         return 1;
     case '+':
-        return cliReadSingleLineReply(fd);
+        return cliReadSingleLineReply(fd,0);
     case ':':
         printf("(integer) ");
-        return cliReadSingleLineReply(fd);
+        return cliReadSingleLineReply(fd,0);
     case '$':
         return cliReadBulkReply(fd);
     case '*':
@@ -254,6 +256,28 @@ static int cliReadReply(int fd) {
     }
 }
 
+static int selectDb(int fd)
+{
+    int retval;
+    sds cmd;
+    char type;
+
+    if (config.dbnum == 0)
+        return 0;
+
+    cmd = sdsempty();
+    cmd = sdscatprintf(cmd,"SELECT %d\r\n",config.dbnum);
+    anetWrite(fd,cmd,sdslen(cmd));
+    anetRead(fd,&type,1);
+    if (type <= 0 || type != '+') return 1;
+    retval = cliReadSingleLineReply(fd,1);
+    if (retval) {
+        close(fd);
+	return retval;
+    }
+    return 0;
+}
+
 static int cliSendCommand(int argc, char **argv) {
     struct redisCommand *rc = lookupCommand(argv[0]);
     int fd, j, retval = 0;
@@ -271,6 +295,13 @@ static int cliSendCommand(int argc, char **argv) {
     }
     if ((fd = cliConnect()) == -1) return 1;
 
+    /* Select db number */
+    retval = selectDb(fd);
+    if (retval) {
+        fprintf(stderr,"Error setting DB num\n");
+        return 1;
+    }
+ 
     while(config.repeat--) {
         /* Build the command to send */
         cmd = sdsempty();
@@ -328,6 +359,9 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-r") && !lastarg) {
             config.repeat = strtoll(argv[i+1],NULL,10);
             i++;
+        } else if (!strcmp(argv[i],"-n") && !lastarg) {
+            config.dbnum = atoi(argv[i+1]);
+            i++;
         } else {
             break;
         }
@@ -360,6 +394,7 @@ int main(int argc, char **argv) {
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
     config.repeat = 1;
+    config.dbnum = 0;
 
     firstarg = parseOptions(argc,argv);
     argc -= firstarg;
@@ -371,8 +406,8 @@ int main(int argc, char **argv) {
         argvcopy[j] = sdsnew(argv[j]);
 
     if (argc < 1) {
-        fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] cmd arg1 arg2 arg3 ... argN\n");
-        fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] -r [repeat_times] cmd arg1 arg2 ... arg(N-1)\n");
+        fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
+        fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
         fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
         fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
         fprintf(stderr, "example: redis-cli get my_passwd\n");