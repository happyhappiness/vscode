@@ -250,11 +250,13 @@ void computeDatasetDigest(unsigned char *final) {
     }
 }
 
+#if defined(USE_JEMALLOC)
 void inputCatSds(void *result, const char *str) {
     /* result is actually a (sds *), so re-cast it here */
     sds *info = (sds *)result;
     *info = sdscat(*info, str);
 }
+#endif
 
 void debugCommand(client *c) {
     if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
@@ -397,6 +399,7 @@ void debugCommand(client *c) {
             snprintf(buf,sizeof(buf),"value:%lu",j);
             val = createStringObject(buf,strlen(buf));
             dbAdd(c->db,key,val);
+            signalModifiedKey(c->db,key);
             decrRefCount(key);
         }
         addReply(c,shared.ok);
@@ -474,8 +477,20 @@ void debugCommand(client *c) {
             sds info = sdsempty();
             je_malloc_stats_print(inputCatSds, &info, NULL);
             addReplyBulkSds(c, info);
+        } else if (!strcasecmp(c->argv[2]->ptr, "purge")) {
+            char tmp[32];
+            unsigned narenas = 0;
+            size_t sz = sizeof(unsigned);
+            if (!je_mallctl("arenas.narenas", &narenas, &sz, NULL, 0)) {
+                sprintf(tmp, "arena.%d.purge", narenas);
+                if (!je_mallctl(tmp, NULL, 0, NULL, 0)) {
+                    addReply(c, shared.ok);
+                    return;
+                }
+            }
+            addReplyError(c, "Error purging dirty pages");
         } else {
-            addReplyErrorFormat(c, "Valid jemalloc debug fields: info");
+            addReplyErrorFormat(c, "Valid jemalloc debug fields: info, purge");
         }
 #else
         addReplyErrorFormat(c, "jemalloc support not available");