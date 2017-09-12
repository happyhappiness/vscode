@@ -67,6 +67,7 @@ static struct config {
 } config;
 
 static void usage();
+char *redisGitSHA1(void);
 
 /*------------------------------------------------------------------------------
  * Utility functions
@@ -351,7 +352,7 @@ static int parseOptions(int argc, char **argv) {
 "automatically used as last argument.\n"
             );
         } else if (!strcmp(argv[i],"-v")) {
-            printf("redis-cli shipped with Redis version %s\n", REDIS_VERSION);
+            printf("redis-cli shipped with Redis version %s (%s)\n", REDIS_VERSION, redisGitSHA1());
             exit(0);
         } else {
             break;