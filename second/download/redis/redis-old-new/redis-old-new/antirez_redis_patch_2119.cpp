@@ -558,6 +558,7 @@ static int rdbSaveBackground(char *filename);
 static robj *createStringObject(char *ptr, size_t len);
 static robj *dupStringObject(robj *o);
 static void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc);
+static void replicationFeedMonitors(list *monitors, int dictid, robj **argv, int argc);
 static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
 static robj *tryObjectEncoding(robj *o);
@@ -2212,7 +2213,7 @@ static void call(redisClient *c, struct redisCommand *cmd) {
         listLength(server.slaves))
         replicationFeedSlaves(server.slaves,c->db->id,c->argv,c->argc);
     if (listLength(server.monitors))
-        replicationFeedSlaves(server.monitors,c->db->id,c->argv,c->argc);
+        replicationFeedMonitors(server.monitors,c->db->id,c->argv,c->argc);
     server.stat_numcommands++;
 }
 
@@ -2467,6 +2468,64 @@ static void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int arg
     if (outv != static_outv) zfree(outv);
 }
 
+static sds sdscatrepr(sds s, char *p, size_t len) {
+    s = sdscatlen(s,"\"",1);
+    while(len--) {
+        switch(*p) {
+        case '\\':
+        case '"':
+            s = sdscatprintf(s,"\\%c",*p);
+            break;
+        case '\n': s = sdscatlen(s,"\\n",1); break;
+        case '\r': s = sdscatlen(s,"\\r",1); break;
+        case '\t': s = sdscatlen(s,"\\t",1); break;
+        case '\a': s = sdscatlen(s,"\\a",1); break;
+        case '\b': s = sdscatlen(s,"\\b",1); break;
+        default:
+            if (isprint(*p))
+                s = sdscatprintf(s,"%c",*p);
+            else
+                s = sdscatprintf(s,"\\x%02x",(unsigned char)*p);
+            break;
+        }
+        p++;
+    }
+    return sdscatlen(s,"\"",1);
+}
+
+static void replicationFeedMonitors(list *monitors, int dictid, robj **argv, int argc) {
+    listNode *ln;
+    listIter li;
+    int j;
+    sds cmdrepr = sdsnew("+");
+    robj *cmdobj;
+    struct timeval tv;
+
+    gettimeofday(&tv,NULL);
+    cmdrepr = sdscatprintf(cmdrepr,"%ld.%ld ",(long)tv.tv_sec,(long)tv.tv_usec);
+    if (dictid != 0) cmdrepr = sdscatprintf(cmdrepr,"(db %d) ", dictid);
+
+    for (j = 0; j < argc; j++) {
+        if (argv[j]->encoding == REDIS_ENCODING_INT) {
+            cmdrepr = sdscatprintf(cmdrepr, "%ld", (long)argv[j]->ptr);
+        } else {
+            cmdrepr = sdscatrepr(cmdrepr,(char*)argv[j]->ptr,
+                        sdslen(argv[j]->ptr));
+        }
+        if (j != argc-1)
+            cmdrepr = sdscatlen(cmdrepr," ",1);
+    }
+    cmdrepr = sdscatlen(cmdrepr,"\r\n",2);
+    cmdobj = createObject(REDIS_STRING,cmdrepr);
+
+    listRewind(monitors,&li);
+    while((ln = listNext(&li))) {
+        redisClient *monitor = ln->value;
+        addReply(monitor,cmdobj);
+    }
+    decrRefCount(cmdobj);
+}
+
 static void processInputBuffer(redisClient *c) {
 again:
     /* Before to process the input buffer, make sure the client is not