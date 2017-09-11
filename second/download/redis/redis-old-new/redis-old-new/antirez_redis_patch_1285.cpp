@@ -446,7 +446,7 @@ static int processMultiBulkItem(redisReader *r) {
     long elements;
     int root = 0;
 
-    /* Set error for nested multi bulks with depth > 2 */
+    /* Set error for nested multi bulks with depth > 7 */
     if (r->ridx == 8) {
         __redisReaderSetError(r,REDIS_ERR_PROTOCOL,
             "No support for nested multi bulk replies with depth > 7");
@@ -564,6 +564,7 @@ redisReader *redisReaderCreate(void) {
     r->errstr[0] = '\0';
     r->fn = &defaultFunctions;
     r->buf = sdsempty();
+    r->maxbuf = REDIS_READER_MAX_BUF;
     if (r->buf == NULL) {
         free(r);
         return NULL;
@@ -590,17 +591,15 @@ int redisReaderFeed(redisReader *r, const char *buf, size_t len) {
 
     /* Copy the provided buffer. */
     if (buf != NULL && len >= 1) {
-#if 0
         /* Destroy internal buffer when it is empty and is quite large. */
-        if (r->len == 0 && sdsavail(r->buf) > 16*1024) {
+        if (r->len == 0 && r->maxbuf != 0 && sdsavail(r->buf) > r->maxbuf) {
             sdsfree(r->buf);
             r->buf = sdsempty();
             r->pos = 0;
 
             /* r->buf should not be NULL since we just free'd a larger one. */
             assert(r->buf != NULL);
         }
-#endif
 
         newbuf = sdscatlen(r->buf,buf,len);
         if (newbuf == NULL) {