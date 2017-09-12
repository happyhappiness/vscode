@@ -799,6 +799,8 @@ static struct redisCommand cmdTable[] = {
     {NULL,NULL,0,0,NULL,0,0,0}
 };
 
+static void usage();
+
 /*============================ Utility functions ============================ */
 
 /* Glob-style pattern matching. */
@@ -1614,12 +1616,15 @@ static void loadServerConfig(char *filename) {
     char buf[REDIS_CONFIGLINE_MAX+1], *err = NULL;
     int linenum = 0;
     sds line = NULL;
+    char *errormsg = "Fatal error, can't open config file '%s'";
+    char *errorbuf = zmalloc(sizeof(char)*(strlen(errormsg)+strlen(filename)));
+    sprintf(errorbuf, errormsg, filename);
 
     if (filename[0] == '-' && filename[1] == '\0')
         fp = stdin;
     else {
         if ((fp = fopen(filename,"r")) == NULL) {
-            redisLog(REDIS_WARNING,"Fatal error, can't open config file");
+            redisLog(REDIS_WARNING, errorbuf);
             exit(1);
         }
     }
@@ -9122,16 +9127,23 @@ static void daemonize(void) {
     }
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
+        if (strcmp(argv[1], "--help") == 0) {
+            usage();
+        }
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