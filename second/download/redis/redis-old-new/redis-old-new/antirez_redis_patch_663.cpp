@@ -252,6 +252,12 @@ void computeDatasetDigest(unsigned char *final) {
     }
 }
 
+void inputCatSds(void *result, const char *str) {
+    /* result is actually a (sds *), so re-cast it here */
+    sds *info = (sds *)result;
+    *info = sdscat(*info, str);
+}
+
 void debugCommand(redisClient *c) {
     if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
         *((char*)-1) = 'x';
@@ -379,6 +385,18 @@ void debugCommand(redisClient *c) {
         errstr = sdsmapchars(errstr,"\n\r","  ",2); /* no newlines in errors. */
         errstr = sdscatlen(errstr,"\r\n",2);
         addReplySds(c,errstr);
+    } else if (!strcasecmp(c->argv[1]->ptr,"jemalloc") && c->argc == 3) {
+#if defined(USE_JEMALLOC)
+        if (!strcasecmp(c->argv[2]->ptr, "info")) {
+            sds info = sdsempty();
+            je_malloc_stats_print(inputCatSds, &info, NULL);
+            addReplyBulkSds(c, info);
+        } else {
+            addReplyErrorFormat(c, "Valid jemalloc debug fields: info");
+        }
+#else
+        addReplyErrorFormat(c, "jemalloc support not available");
+#endif
     } else {
         addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
             (char*)c->argv[1]->ptr);