@@ -46,7 +46,6 @@ robj *lookupKeyRead(redisDb *db, robj *key) {
 
 robj *lookupKeyWrite(redisDb *db, robj *key) {
     deleteIfVolatile(db,key);
-    touchWatchedKey(db,key);
     return lookupKey(db,key);
 }
 
@@ -332,6 +331,7 @@ void renameGenericCommand(redisClient *c, int nx) {
         dbReplace(c->db,c->argv[2],o);
     }
     dbDelete(c->db,c->argv[1]);
+    touchWatchedKey(c->db,c->argv[1]);
     touchWatchedKey(c->db,c->argv[2]);
     server.dirty++;
     addReply(c,nx ? shared.cone : shared.ok);
@@ -506,5 +506,3 @@ void ttlCommand(redisClient *c) {
     }
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
 }
-
-