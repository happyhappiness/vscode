@@ -79,7 +79,7 @@ void getsetCommand(redisClient *c) {
 void mgetCommand(redisClient *c) {
     int j;
 
-    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-1));
+    addReplyMultiBulkLen(c,c->argc-1);
     for (j = 1; j < c->argc; j++) {
         robj *o = lookupKeyRead(c->db,c->argv[j]);
         if (o == NULL) {