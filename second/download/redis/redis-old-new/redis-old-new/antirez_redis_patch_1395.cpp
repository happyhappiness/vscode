@@ -2231,7 +2231,8 @@ void usage() {
     fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf] [options]\n");
     fprintf(stderr,"       ./redis-server - (read config from stdin)\n");
     fprintf(stderr,"       ./redis-server -v or --version\n");
-    fprintf(stderr,"       ./redis-server -h or --help\n\n");
+    fprintf(stderr,"       ./redis-server -h or --help\n");
+    fprintf(stderr,"       ./redis-server --test-memory <megabytes>\n\n");
     fprintf(stderr,"Examples:\n");
     fprintf(stderr,"       ./redis-server (run the server with default conf)\n");
     fprintf(stderr,"       ./redis-server /etc/redis/6379.conf\n");
@@ -2287,6 +2288,8 @@ void setupSignalHandlers(void) {
     return;
 }
 
+void memtest(size_t megabytes, int passes);
+
 int main(int argc, char **argv) {
     long long start;
     struct timeval tv;
@@ -2308,6 +2311,17 @@ int main(int argc, char **argv) {
             strcmp(argv[1], "--version") == 0) version();
         if (strcmp(argv[1], "--help") == 0 ||
             strcmp(argv[1], "-h") == 0) usage();
+        if (strcmp(argv[1], "--test-memory") == 0) {
+            if (argc == 3) {
+                memtest(atoi(argv[2]),10000);
+                exit(0);
+            } else {
+                fprintf(stderr,"Please specify the amount of memory to test in megabytes.\n");
+                fprintf(stderr,"Example: ./redis-server --test-memory 4096\n\n");
+                exit(1);
+            }
+        }
+
         /* First argument is the config file name? */
         if (argv[j][0] != '-' || argv[j][1] != '-')
             configfile = argv[j++];