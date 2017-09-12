@@ -9200,6 +9200,7 @@ static void version() {
 
 static void usage() {
     fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
+    fprintf(stderr,"       ./redis-server - (read config from stdin)\n");
     exit(1);
 }
 