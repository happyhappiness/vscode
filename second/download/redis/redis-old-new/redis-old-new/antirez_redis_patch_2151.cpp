@@ -5937,10 +5937,8 @@ static void hsetCommand(redisClient *c) {
         decrRefCount(valobj);
         o->ptr = zm;
 
-        /* And here there is the second check for hash conversion...
-         * we want to do it only if the operation was not just an update as
-         * zipmapLen() is O(N). */
-        if (!update && zipmapLen(zm) > server.hash_max_zipmap_entries)
+        /* And here there is the second check for hash conversion. */
+        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
             convertToRealHash(o);
     } else {
         tryObjectEncoding(c->argv[2]);
@@ -5958,7 +5956,6 @@ static void hsetCommand(redisClient *c) {
 }
 
 static void hincrbyCommand(redisClient *c) {
-    int update = 0;
     long long value = 0, incr = 0;
     robj *o = lookupKeyWrite(c->db,c->argv[1]);
 
@@ -5995,13 +5992,12 @@ static void hincrbyCommand(redisClient *c) {
         value += incr;
         sds svalue = sdscatprintf(sdsempty(),"%lld",value);
         zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
-            (unsigned char*)svalue,sdslen(svalue),&update);
+            (unsigned char*)svalue,sdslen(svalue),NULL);
         sdsfree(svalue);
         o->ptr = zm;
 
-        /* Check if the zipmap needs to be converted
-         * if this was not an update. */
-        if (!update && zipmapLen(zm) > server.hash_max_zipmap_entries)
+        /* Check if the zipmap needs to be converted. */
+        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
             convertToRealHash(o);
     } else {
         robj *hval;