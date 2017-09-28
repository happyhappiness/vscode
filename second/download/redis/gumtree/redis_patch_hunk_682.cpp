 static void __redisSetErrorFromErrno(redisContext *c, int type, const char *prefix) {
     char buf[128] = { 0 };
     size_t len = 0;
 
     if (prefix != NULL)
         len = snprintf(buf,sizeof(buf),"%s: ",prefix);
-    strerror_r(errno,buf+len,sizeof(buf)-len);
+    __redis_strerror_r(errno, (char *)(buf + len), sizeof(buf) - len);
     __redisSetError(c,type,buf);
 }
 
 static int redisSetReuseAddr(redisContext *c) {
     int on = 1;
     if (setsockopt(c->fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
