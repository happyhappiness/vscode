@@ -51,6 +51,7 @@
 static struct config {
     char *hostip;
     int hostport;
+    char *hostsocket;
     long repeat;
     int dbnum;
     int interactive;
@@ -119,9 +120,17 @@ static int cliConnect(int force) {
 
     if (fd == ANET_ERR || force) {
         if (force) close(fd);
-        fd = anetTcpConnect(err,config.hostip,config.hostport);
+        if (config.hostsocket == NULL) {
+            fd = anetTcpConnect(err,config.hostip,config.hostport);
+        } else {
+            fd = anetUnixConnect(err,config.hostsocket);
+        }
         if (fd == ANET_ERR) {
-            fprintf(stderr, "Could not connect to Redis at %s:%d: %s", config.hostip, config.hostport, err);
+            fprintf(stderr,"Could not connect to Redis at ");
+            if (config.hostsocket == NULL)
+                fprintf(stderr,"%s:%d: %s",config.hostip,config.hostport,err);
+            else
+                fprintf(stderr,"%s: %s",config.hostsocket,err);
             return -1;
         }
         anetTcpNoDelay(NULL,fd);
@@ -362,6 +371,9 @@ static int parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
             config.hostport = atoi(argv[i+1]);
             i++;
+        } else if (!strcmp(argv[i],"-s") && !lastarg) {
+            config.hostsocket = argv[i+1];
+            i++;
         } else if (!strcmp(argv[i],"-r") && !lastarg) {
             config.repeat = strtoll(argv[i+1],NULL,10);
             i++;
@@ -410,7 +422,7 @@ static sds readArgFromStdin(void) {
 }
 
 static void usage() {
-    fprintf(stderr, "usage: redis-cli [-iv] [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
+    fprintf(stderr, "usage: redis-cli [-iv] [-h host] [-p port] [-s /path/to/socket] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
     fprintf(stderr, "usage: echo \"argN\" | redis-cli -x [options] cmd arg1 arg2 ... arg(N-1)\n\n");
     fprintf(stderr, "example: cat /etc/passwd | redis-cli -x set my_passwd\n");
     fprintf(stderr, "example: redis-cli get my_passwd\n");
@@ -497,6 +509,7 @@ int main(int argc, char **argv) {
 
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
+    config.hostsocket = NULL;
     config.repeat = 1;
     config.dbnum = 0;
     config.interactive = 0;