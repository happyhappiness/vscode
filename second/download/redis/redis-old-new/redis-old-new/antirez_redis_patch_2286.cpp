@@ -1104,7 +1104,7 @@ static void initServer() {
     aeCreateTimeEvent(server.el, 1000, serverCron, NULL, NULL);
 
     if (server.appendonly) {
-        server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT);
+        server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
         if (server.appendfd == -1) {
             redisLog(REDIS_WARNING, "Can't open the append-only file: %s",
                 strerror(errno));
@@ -1725,7 +1725,7 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
      * there is much to do about the whole server stopping for power problems
      * or alike */
      nwritten = write(server.appendfd,buf,sdslen(buf));
-     if (nwritten != (unsigned)sdslen(buf)) {
+     if (nwritten != (signed)sdslen(buf)) {
         /* Ooops, we are in troubles. The best thing to do for now is
          * to simply exit instead to give the illusion that everything is
          * working as expected. */