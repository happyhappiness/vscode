@@ -226,7 +226,7 @@ void computeDatasetDigest(unsigned char *final) {
                 robj *obj;
 
                 hi = hashTypeInitIterator(o);
-                while (hashTypeNext(hi) != REDIS_ERR) {
+                while (hashTypeNext(hi) != C_ERR) {
                     unsigned char eledigest[20];
 
                     memset(eledigest,0,20);
@@ -269,20 +269,20 @@ void debugCommand(client *c) {
         if (c->argc >= 3) c->argv[2] = tryObjectEncoding(c->argv[2]);
         serverAssertWithInfo(c,c->argv[0],1 == 2);
     } else if (!strcasecmp(c->argv[1]->ptr,"reload")) {
-        if (rdbSave(server.rdb_filename) != REDIS_OK) {
+        if (rdbSave(server.rdb_filename) != C_OK) {
             addReply(c,shared.err);
             return;
         }
         emptyDb(NULL);
-        if (rdbLoad(server.rdb_filename) != REDIS_OK) {
+        if (rdbLoad(server.rdb_filename) != C_OK) {
             addReplyError(c,"Error trying to load the RDB dump");
             return;
         }
         serverLog(REDIS_WARNING,"DB reloaded by DEBUG RELOAD");
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
         emptyDb(NULL);
-        if (loadAppendOnlyFile(server.aof_filename) != REDIS_OK) {
+        if (loadAppendOnlyFile(server.aof_filename) != C_OK) {
             addReply(c,shared.err);
             return;
         }
@@ -370,7 +370,7 @@ void debugCommand(client *c) {
         robj *key, *val;
         char buf[128];
 
-        if (getLongFromObjectOrReply(c, c->argv[2], &keys, NULL) != REDIS_OK)
+        if (getLongFromObjectOrReply(c, c->argv[2], &keys, NULL) != C_OK)
             return;
         dictExpand(c->db->dict,keys);
         for (j = 0; j < keys; j++) {
@@ -434,7 +434,7 @@ void debugCommand(client *c) {
         sds stats = sdsempty();
         char buf[4096];
 
-        if (getLongFromObjectOrReply(c, c->argv[2], &dbid, NULL) != REDIS_OK)
+        if (getLongFromObjectOrReply(c, c->argv[2], &dbid, NULL) != C_OK)
             return;
         if (dbid < 0 || dbid >= server.dbnum) {
             addReplyError(c,"Out of range database");