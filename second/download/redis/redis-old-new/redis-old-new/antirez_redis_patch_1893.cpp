@@ -364,7 +364,7 @@ static int parseOptions(int argc, char **argv) {
 "automatically used as last argument.\n"
             );
         } else if (!strcmp(argv[i],"-v")) {
-            printf("redis-cli shipped with Redis verison %s\n", REDIS_VERSION);
+            printf("redis-cli shipped with Redis version %s\n", REDIS_VERSION);
             exit(0);
         } else {
             break;