@@ -716,6 +716,7 @@ static void repl() {
 
             if (argv == NULL) {
                 printf("Invalid argument(s)\n");
+                free(line);
                 continue;
             } else if (argc > 0) {
                 if (strcasecmp(argv[0],"quit") == 0 ||