@@ -212,26 +212,7 @@ void computeDatasetDigest(unsigned char *final) {
 void debugCommand(redisClient *c) {
     if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
         *((char*)-1) = 'x';
-    } else if (!strcasecmp(c->argv[1]->ptr,"flushcache")) {
-        if (!server.ds_enabled) {
-            addReplyError(c, "DEBUG FLUSHCACHE called with diskstore off.");
-            return;
-        } else if (server.bgsavethread != (pthread_t) -1) {
-            addReplyError(c, "Can't flush cache while BGSAVE is in progress.");
-            return;
-        } else {
-            /* To flush the whole cache we need to wait for everything to
-             * be flushed on disk... */
-            cacheForcePointInTime();
-            emptyDb();
-            addReply(c,shared.ok);
-            return;
-        }
     } else if (!strcasecmp(c->argv[1]->ptr,"reload")) {
-        if (server.ds_enabled) {
-            addReply(c,shared.ok);
-            return;
-        }
         if (rdbSave(server.dbfilename) != REDIS_OK) {
             addReply(c,shared.err);
             return;
@@ -256,7 +237,6 @@ void debugCommand(redisClient *c) {
         robj *val;
         char *strenc;
 
-        if (server.ds_enabled) lookupKeyRead(c->db,c->argv[2]);
         if ((de = dictFind(c->db->dict,c->argv[2]->ptr)) == NULL) {
             addReply(c,shared.nokeyerr);
             return;