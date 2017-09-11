@@ -1153,7 +1153,6 @@ void adjustOpenFilesLimit(void) {
     rlim_t maxfiles = server.maxclients+32;
     struct rlimit limit;
 
-    if (maxfiles < 1024) maxfiles = 1024;
     if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
         redisLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
             strerror(errno));