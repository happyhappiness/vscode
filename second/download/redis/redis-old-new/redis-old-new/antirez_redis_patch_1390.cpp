@@ -2313,7 +2313,7 @@ int main(int argc, char **argv) {
             strcmp(argv[1], "-h") == 0) usage();
         if (strcmp(argv[1], "--test-memory") == 0) {
             if (argc == 3) {
-                memtest(atoi(argv[2]),300);
+                memtest(atoi(argv[2]),50);
                 exit(0);
             } else {
                 fprintf(stderr,"Please specify the amount of memory to test in megabytes.\n");