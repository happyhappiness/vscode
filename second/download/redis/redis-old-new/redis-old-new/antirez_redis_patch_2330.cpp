@@ -4002,6 +4002,8 @@ int main(int argc, char **argv) {
     } else if (argc > 2) {
         fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
         exit(1);
+    } else {
+        redisLog(REDIS_WARNING,"Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'");
     }
     initServer();
     if (server.daemonize) daemonize();