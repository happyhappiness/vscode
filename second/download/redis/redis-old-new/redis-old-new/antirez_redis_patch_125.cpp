@@ -252,14 +252,6 @@ void computeDatasetDigest(unsigned char *final) {
     }
 }
 
-#if defined(USE_JEMALLOC)
-void inputCatSds(void *result, const char *str) {
-    /* result is actually a (sds *), so re-cast it here */
-    sds *info = (sds *)result;
-    *info = sdscat(*info, str);
-}
-#endif
-
 void debugCommand(client *c) {
     if (c->argc == 1) {
         addReplyError(c,"You must specify a subcommand for DEBUG. Try DEBUG HELP for info.");
@@ -303,10 +295,6 @@ void debugCommand(client *c) {
         "structsize -- Return the size of different Redis core C structures.");
         blen++; addReplyStatus(c,
         "htstats <dbid> -- Return hash table statistics of the specified Redis database.");
-        blen++; addReplyStatus(c,
-        "jemalloc info  -- Show internal jemalloc statistics.");
-        blen++; addReplyStatus(c,
-        "jemalloc purge -- Force jemalloc to release unused memory.");
         setDeferredMultiBulkLength(c,blenp,blen);
     } else if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
         *((char*)-1) = 'x';
@@ -520,30 +508,6 @@ void debugCommand(client *c) {
         stats = sdscat(stats,buf);
 
         addReplyBulkSds(c,stats);
-    } else if (!strcasecmp(c->argv[1]->ptr,"jemalloc") && c->argc == 3) {
-#if defined(USE_JEMALLOC)
-        if (!strcasecmp(c->argv[2]->ptr, "info")) {
-            sds info = sdsempty();
-            je_malloc_stats_print(inputCatSds, &info, NULL);
-            addReplyBulkSds(c, info);
-        } else if (!strcasecmp(c->argv[2]->ptr, "purge")) {
-            char tmp[32];
-            unsigned narenas = 0;
-            size_t sz = sizeof(unsigned);
-            if (!je_mallctl("arenas.narenas", &narenas, &sz, NULL, 0)) {
-                sprintf(tmp, "arena.%d.purge", narenas);
-                if (!je_mallctl(tmp, NULL, 0, NULL, 0)) {
-                    addReply(c, shared.ok);
-                    return;
-                }
-            }
-            addReplyError(c, "Error purging dirty pages");
-        } else {
-            addReplyErrorFormat(c, "Valid jemalloc debug fields: info, purge");
-        }
-#else
-        addReplyErrorFormat(c, "jemalloc support not available");
-#endif
     } else {
         addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
             (char*)c->argv[1]->ptr);