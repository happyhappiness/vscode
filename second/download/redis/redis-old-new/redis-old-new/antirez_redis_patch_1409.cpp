@@ -447,9 +447,9 @@ static int processMultiBulkItem(redisReader *r) {
     int root = 0;
 
     /* Set error for nested multi bulks with depth > 2 */
-    if (r->ridx == 3) {
+    if (r->ridx == 8) {
         __redisReaderSetError(r,REDIS_ERR_PROTOCOL,
-            "No support for nested multi bulk replies with depth > 2");
+            "No support for nested multi bulk replies with depth > 7");
         return REDIS_ERR;
     }
 
@@ -590,6 +590,7 @@ int redisReaderFeed(redisReader *r, const char *buf, size_t len) {
 
     /* Copy the provided buffer. */
     if (buf != NULL && len >= 1) {
+#if 0
         /* Destroy internal buffer when it is empty and is quite large. */
         if (r->len == 0 && sdsavail(r->buf) > 16*1024) {
             sdsfree(r->buf);
@@ -599,6 +600,7 @@ int redisReaderFeed(redisReader *r, const char *buf, size_t len) {
             /* r->buf should not be NULL since we just free'd a larger one. */
             assert(r->buf != NULL);
         }
+#endif
 
         newbuf = sdscatlen(r->buf,buf,len);
         if (newbuf == NULL) {
@@ -1067,7 +1069,7 @@ int redisSetTimeout(redisContext *c, struct timeval tv) {
  * After this function is called, you may use redisContextReadReply to
  * see if there is a reply available. */
 int redisBufferRead(redisContext *c) {
-    char buf[2048];
+    char buf[1024*16];
     int nread;
 
     /* Return early when the context has seen an error. */