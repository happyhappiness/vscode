@@ -1449,8 +1449,8 @@ void initServerConfig(void) {
     server.maxmemory_samples = REDIS_DEFAULT_MAXMEMORY_SAMPLES;
     server.hash_max_ziplist_entries = REDIS_HASH_MAX_ZIPLIST_ENTRIES;
     server.hash_max_ziplist_value = REDIS_HASH_MAX_ZIPLIST_VALUE;
-    server.list_max_ziplist_entries = REDIS_LIST_MAX_ZIPLIST_ENTRIES;
-    server.list_max_ziplist_value = REDIS_LIST_MAX_ZIPLIST_VALUE;
+    server.list_max_ziplist_size = REDIS_LIST_MAX_ZIPLIST_SIZE;
+    server.list_compress_depth = REDIS_LIST_COMPRESS_DEPTH;
     server.set_max_intset_entries = REDIS_SET_MAX_INTSET_ENTRIES;
     server.zset_max_ziplist_entries = REDIS_ZSET_MAX_ZIPLIST_ENTRIES;
     server.zset_max_ziplist_value = REDIS_ZSET_MAX_ZIPLIST_VALUE;
@@ -3058,11 +3058,7 @@ void infoCommand(redisClient *c) {
         addReply(c,shared.syntaxerr);
         return;
     }
-    sds info = genRedisInfoString(section);
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
-        (unsigned long)sdslen(info)));
-    addReplySds(c,info);
-    addReply(c,shared.crlf);
+    addReplyBulkSds(c, genRedisInfoString(section));
 }
 
 void monitorCommand(redisClient *c) {
@@ -3659,6 +3655,32 @@ int redisIsSupervised(void) {
 int main(int argc, char **argv) {
     struct timeval tv;
 
+#ifdef REDIS_TEST
+    if (argc == 3 && !strcasecmp(argv[1], "test")) {
+        if (!strcasecmp(argv[2], "ziplist")) {
+            return ziplistTest(argc, argv);
+        } else if (!strcasecmp(argv[2], "quicklist")) {
+            quicklistTest(argc, argv);
+        } else if (!strcasecmp(argv[2], "intset")) {
+            return intsetTest(argc, argv);
+        } else if (!strcasecmp(argv[2], "zipmap")) {
+            return zipmapTest(argc, argv);
+        } else if (!strcasecmp(argv[2], "sha1test")) {
+            return sha1Test(argc, argv);
+        } else if (!strcasecmp(argv[2], "util")) {
+            return utilTest(argc, argv);
+        } else if (!strcasecmp(argv[2], "sds")) {
+            return sdsTest(argc, argv);
+        } else if (!strcasecmp(argv[2], "endianconv")) {
+            return endianconvTest(argc, argv);
+        } else if (!strcasecmp(argv[2], "crc64")) {
+            return crc64Test(argc, argv);
+        }
+
+        return -1; /* test not found */
+    }
+#endif
+
     /* We need to initialize our libraries, and the server configuration. */
 #ifdef INIT_SETPROCTITLE_REPLACEMENT
     spt_init(argc, argv);