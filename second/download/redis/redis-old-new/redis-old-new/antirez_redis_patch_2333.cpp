@@ -361,6 +361,7 @@ static void mgetCommand(redisClient *c);
 static void monitorCommand(redisClient *c);
 static void expireCommand(redisClient *c);
 static void getSetCommand(redisClient *c);
+static void ttlCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -422,6 +423,7 @@ static struct redisCommand cmdTable[] = {
     {"info",infoCommand,1,REDIS_CMD_INLINE},
     {"monitor",monitorCommand,1,REDIS_CMD_INLINE},
     {"expire",expireCommand,3,REDIS_CMD_INLINE},
+    {"ttl",ttlCommand,2,REDIS_CMD_INLINE},
     {NULL,NULL,0,0}
 };
 
@@ -3602,6 +3604,18 @@ static void expireCommand(redisClient *c) {
     }
 }
 
+static void ttlCommand(redisClient *c) {
+    time_t expire;
+    int ttl = -1;
+
+    expire = getExpire(c->db,c->argv[1]);
+    if (expire != -1) {
+        ttl = (int) (expire-time(NULL));
+        if (ttl < 0) ttl = -1;
+    }
+    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
+}
+
 /* =============================== Replication  ============================= */
 
 static int syncWrite(int fd, char *ptr, ssize_t size, int timeout) {