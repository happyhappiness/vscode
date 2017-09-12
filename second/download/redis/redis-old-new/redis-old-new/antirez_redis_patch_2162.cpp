@@ -799,6 +799,8 @@ static struct redisCommand cmdTable[] = {
     {NULL,NULL,0,0,NULL,0,0,0}
 };
 
+static void usage();
+
 /*============================ Utility functions ============================ */
 
 /* Glob-style pattern matching. */
@@ -9168,19 +9170,23 @@ static void version() {
     exit(0);
 }
 
+static void usage() {
+    fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
+    exit(1);
+}
+
 int main(int argc, char **argv) {
     time_t start;
 
     initServerConfig();
     if (argc == 2) {
-        if ((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "--version") == 0)) {
-            version();
-        }
+        if (strcmp(argv[1], "-v") == 0 ||
+            strcmp(argv[1], "--version") == 0) version();
+        if (strcmp(argv[1], "--help") == 0) usage();
         resetServerSaveParams();
         loadServerConfig(argv[1]);
-    } else if (argc > 2) {
-        fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
-        exit(1);
+    } else if ((argc > 2)) {
+        usage();
     } else {
         redisLog(REDIS_WARNING,"Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'");
     }