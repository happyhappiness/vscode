@@ -50,7 +50,7 @@ typedef struct redisReader {
     size_t pos; /* buffer cursor */
     size_t len; /* buffer length */
 
-    redisReadTask rstack[3]; /* stack of read tasks */
+    redisReadTask rstack[9]; /* stack of read tasks */
     int ridx; /* index of stack */
     void *privdata; /* user-settable arbitrary field */
 } redisReader;
@@ -347,9 +347,9 @@ static int processMultiBulkItem(redisReader *r) {
     int root = 0;
 
     /* Set error for nested multi bulks with depth > 1 */
-    if (r->ridx == 2) {
+    if (r->ridx == 8) {
         redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
-            "No support for nested multi bulk replies with depth > 1"));
+            "No support for nested multi bulk replies with depth > 7"));
         return -1;
     }
 