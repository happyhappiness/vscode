@@ -52,7 +52,6 @@ static struct config {
     const char *hostip;
     int hostport;
     const char *hostsocket;
-    int debug;
     int numclients;
     int requests;
     int liveclients;
@@ -370,8 +369,6 @@ int parseOptions(int argc, const char **argv) {
             config.quiet = 1;
         } else if (!strcmp(argv[i],"-l")) {
             config.loop = 1;
-        } else if (!strcmp(argv[i],"-D")) {
-            config.debug = 1;
         } else if (!strcmp(argv[i],"-I")) {
             config.idlemode = 1;
         } else if (!strcmp(argv[i],"--help")) {
@@ -410,7 +407,6 @@ int parseOptions(int argc, const char **argv) {
     printf(" -q                 Quiet. Just show query/sec values\n");
     printf(" -l                 Loop. Run the tests forever\n");
     printf(" -I                 Idle mode. Just open N idle connections and wait.\n");
-    printf(" -D                 Debug mode. more verbose.\n");
     exit(exit_status);
 }
 
@@ -436,7 +432,6 @@ int main(int argc, const char **argv) {
     signal(SIGHUP, SIG_IGN);
     signal(SIGPIPE, SIG_IGN);
 
-    config.debug = 0;
     config.numclients = 50;
     config.requests = 10000;
     config.liveclients = 0;
@@ -479,7 +474,7 @@ int main(int argc, const char **argv) {
         sds title = sdsnew(argv[0]);
         for (i = 1; i < argc; i++) {
             title = sdscatlen(title, " ", 1);
-            title = sdscatlen(title, (char*)argv[i], strlen(argv[1]));
+            title = sdscatlen(title, (char*)argv[i], strlen(argv[i]));
         }
 
         do {