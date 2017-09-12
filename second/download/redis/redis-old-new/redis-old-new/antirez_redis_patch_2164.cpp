@@ -1102,6 +1102,8 @@ static dictType keylistDictType = {
     dictListDestructor          /* val destructor */
 };
 
+static void version();
+
 /* ========================= Random utility functions ======================= */
 
 /* Redis generally does not try to recover from out of memory conditions
@@ -9158,11 +9160,19 @@ static void daemonize(void) {
     }
 }
 
+static void version() {
+    printf("Redis server version %s\n", REDIS_VERSION);
+    exit(0);
+}
+
 int main(int argc, char **argv) {
     time_t start;
 
     initServerConfig();
     if (argc == 2) {
+        if ((strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "--version") == 0)) {
+            version();
+        }
         resetServerSaveParams();
         loadServerConfig(argv[1]);
     } else if (argc > 2) {