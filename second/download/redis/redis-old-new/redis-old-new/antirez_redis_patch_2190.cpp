@@ -420,7 +420,7 @@ static void usage() {
     fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
     fprintf(stderr, "example: redis-cli get my_passwd\n");
     fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
-    fprintf(stderr, "\nRun in interactive mode: redis-cli -i \n");
+    fprintf(stderr, "\nRun in interactive mode: redis-cli -i or just don't pass any command\n");
     exit(1);
 }
 
@@ -486,12 +486,10 @@ int main(int argc, char **argv) {
     config.interactive = 0;
 
     firstarg = parseOptions(argc,argv);
-
     argc -= firstarg;
     argv += firstarg;
 
-    if (config.interactive == 1) repl();
-    if (argc < 1) usage();
+    if (argc == 0 || config.interactive == 1) repl();
 
     argvcopy = convertToSds(argc, argv);
 