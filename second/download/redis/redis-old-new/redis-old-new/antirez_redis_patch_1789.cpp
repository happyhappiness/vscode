@@ -80,6 +80,7 @@ typedef struct _client {
     redisContext *context;
     int state;
     sds obuf;
+    char *randptr;
     unsigned int written; /* bytes of 'obuf' already written */
     int replytype;
     long long start; /* start time of a request */
@@ -145,16 +146,29 @@ static void resetClient(client c) {
 }
 
 static void randomizeClientKey(client c) {
-    char *p;
+    char *p, *newline;
     char buf[32];
     long r;
 
-    p = strstr(c->obuf, "_rand");
-    if (!p) return;
-    p += 5;
+    if (c->randptr == NULL) return;
+
+    /* Check if we have to randomize (only once per connection) */
+    if (c->randptr == (void*)-1) {
+        p = strstr(c->obuf,":rand:");
+        if (!p) {
+            c->randptr = NULL;
+            return;
+        } else {
+            newline = strstr(p,"\r\n");
+            assert(newline-(p+6) == 12); /* 12 chars for randomness */
+            c->randptr = p+6;
+        }
+    }
+
+    /* Set random number in output buffer */
     r = random() % config.randomkeys_keyspacelen;
-    sprintf(buf,"%ld",r);
-    memcpy(p,buf,strlen(buf));
+    snprintf(buf,sizeof(buf),"%012ld",r);
+    memcpy(c->randptr,buf,12);
 }
 
 static void clientDone(client c) {
@@ -253,7 +267,8 @@ static client createClient(int replytype) {
     }
     c->replytype = replytype;
     c->state = CLIENT_CONNECTING;
-    c->obuf = sdsempty();
+    c->obuf = NULL;
+    c->randptr = (void*)-1;
     c->written = 0;
     redisSetReplyObjectFunctions(c->context,NULL);
     aeCreateFileEvent(config.el,c->context->fd,AE_WRITABLE,writeHandler,c);
@@ -265,7 +280,6 @@ static client createClient(int replytype) {
 static void createMissingClients(client c) {
     while(config.liveclients < config.numclients) {
         client new = createClient(c->replytype);
-        sdsfree(new->obuf);
         new->obuf = sdsdup(c->obuf);
         if (config.randomkeys) randomizeClientKey(c);
     }
@@ -441,114 +455,148 @@ int main(int argc, char **argv) {
     }
 
     do {
-        char *data = zmalloc(config.datasize+1);
+        char *data, *cmd;
+        int len;
+
+        data = zmalloc(config.datasize+1);
         memset(data,'x',config.datasize);
         data[config.datasize] = '\0';
 
-        prepareForBenchmark("PING");
+        prepareForBenchmark("PING (inline)");
         c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"PING\r\n");
+        c->obuf = sdscat(sdsempty(),"PING\r\n");
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
-        prepareForBenchmark("PING (multi bulk)");
+        prepareForBenchmark("PING");
         c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"*1\r\n$4\r\nPING\r\n");
+        len = redisFormatCommand(&cmd,"PING");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
-        prepareForBenchmark("MSET (10 keys, multi bulk)");
+        prepareForBenchmark("MSET (10 keys)");
         c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
-        for (i = 0; i < 10; i++) {
-            c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
+        {
+            const char *argv[11];
+            argv[0] = "MSET";
+            for (i = 1; i < 11; i++)
+                argv[i] = data;
+            len = redisFormatCommandArgv(&cmd,11,argv,NULL);
+            c->obuf = sdsnewlen(cmd,len);
+            free(cmd);
+        }
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("SET");
         c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"*3\r\n$3\r\nSET\r\n$20\r\nfoo_rand000000000000\r\n");
-        c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
+        len = redisFormatCommand(&cmd,"SET foo:rand:000000000000 %s",data);
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("GET");
         c = createClient(REDIS_REPLY_STRING);
-        c->obuf = sdscat(c->obuf,"GET foo_rand000000000000\r\n");
+        len = redisFormatCommand(&cmd,"GET foo:rand:000000000000");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("INCR");
         c = createClient(REDIS_REPLY_INTEGER);
-        c->obuf = sdscat(c->obuf,"INCR counter_rand000000000000\r\n");
+        len = redisFormatCommand(&cmd,"INCR counter:rand:000000000000");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LPUSH");
         c = createClient(REDIS_REPLY_INTEGER);
-        c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
+        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LPOP");
         c = createClient(REDIS_REPLY_STRING);
-        c->obuf = sdscat(c->obuf,"LPOP mylist\r\n");
+        len = redisFormatCommand(&cmd,"LPOP mylist");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("SADD");
         c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"SADD myset counter_rand000000000000\r\n");
+        len = redisFormatCommand(&cmd,"SADD myset counter:rand:000000000000");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("SPOP");
         c = createClient(REDIS_REPLY_STRING);
-        c->obuf = sdscat(c->obuf,"SPOP myset\r\n");
+        len = redisFormatCommand(&cmd,"SPOP myset");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LPUSH (again, in order to bench LRANGE)");
         c = createClient(REDIS_REPLY_STATUS);
-        c->obuf = sdscat(c->obuf,"LPUSH mylist bar\r\n");
+        len = redisFormatCommand(&cmd,"LPUSH mylist %s",data);
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LRANGE (first 100 elements)");
         c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 99\r\n");
+        len = redisFormatCommand(&cmd,"LRANGE mylist 0 99");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LRANGE (first 300 elements)");
         c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 299\r\n");
+        len = redisFormatCommand(&cmd,"LRANGE mylist 0 299");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LRANGE (first 450 elements)");
         c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 449\r\n");
+        len = redisFormatCommand(&cmd,"LRANGE mylist 0 449");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();
 
         prepareForBenchmark("LRANGE (first 600 elements)");
         c = createClient(REDIS_REPLY_ARRAY);
-        c->obuf = sdscat(c->obuf,"LRANGE mylist 0 599\r\n");
+        len = redisFormatCommand(&cmd,"LRANGE mylist 0 599");
+        c->obuf = sdsnewlen(cmd,len);
+        free(cmd);
         createMissingClients(c);
         aeMain(config.el);
         endBenchmark();