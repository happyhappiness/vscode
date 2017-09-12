@@ -125,25 +125,23 @@ long process(FILE *fp) {
 }
 
 int main(int argc, char **argv) {
-    /* expect the first argument to be the dump file */
-    if (argc <= 1) {
-        printf("Usage: %s [--fix] <file.aof>\n", argv[0]);
-        exit(0);
-    }
-
     char *filename;
     int fix = 0;
-    if (argc == 3) {
+
+    if (argc < 2) {
+        printf("Usage: %s [--fix] <file.aof>\n", argv[0]);
+        exit(1);
+    } else if (argc == 2) {
+        filename = argv[1];
+    } else if (argc == 3) {
         if (strcmp(argv[1],"--fix") != 0) {
             printf("Invalid argument: %s\n", argv[1]);
             exit(1);
         }
-        fix = 1;
         filename = argv[2];
-    } else if (argc == 2) {
-        filename = argv[1];
+        fix = 1;
     } else {
-        printf("Invalid argument");
+        printf("Invalid arguments\n");
         exit(1);
     }
 