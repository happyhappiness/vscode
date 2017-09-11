@@ -1,4 +1,5 @@
 #include "redis.h"
+#include "sha1.h"
 
 #include <arpa/inet.h>
 #include <fcntl.h>
@@ -1457,9 +1458,80 @@ void clusterCommand(redisClient *c) {
 }
 
 /* -----------------------------------------------------------------------------
- * RESTORE and MIGRATE commands
+ * DUMP, RESTORE and MIGRATE commands
  * -------------------------------------------------------------------------- */
 
+/* Generates a DUMP-format representation of the object 'o', adding it to the
+ * io stream pointed by 'rio'. This function can't fail. */
+void createDumpPayload(rio *payload, robj *o) {
+    unsigned char hash[20], buf[2];
+    SHA1_CTX ctx;
+
+    /* Serialize the object in a RDB-like format. It consist of an object type
+     * byte followed by the serialized object. This is understood by RESTORE. */
+    rioInitWithBuffer(payload,sdsempty());
+    redisAssert(rdbSaveObjectType(payload,o));
+    redisAssert(rdbSaveObject(payload,o));
+
+    /* Write the footer, this is how it looks like:
+     * ----------------+---------------------+--------------+
+     * ... RDB payload | 2 bytes RDB version | 8 bytes SHA1 |
+     * ----------------+---------------------+--------------+
+     * The SHA1 is just 8 bytes of truncated SHA1 of everything excluding itself.
+     * The 2 bytes RDB version is a little endian unsigned integer.  */
+    buf[0] = (REDIS_RDB_VERSION >> 8) & 0xff;
+    buf[1] = REDIS_RDB_VERSION & 0xff;
+    payload->io.buffer.ptr = sdscatlen(payload->io.buffer.ptr,buf,2);
+
+    SHA1Init(&ctx);
+    SHA1Update(&ctx,(unsigned char*)payload->io.buffer.ptr,
+                    sdslen(payload->io.buffer.ptr));
+    SHA1Final(hash,&ctx);
+    payload->io.buffer.ptr = sdscatlen(payload->io.buffer.ptr,hash,8);
+}
+
+/* Verify that the RDB version of the dump payload matches the one of this Redis
+ * instance and that the truncated SHA1 is ok.
+ * If the DUMP payload looks valid REDIS_OK is returned, otherwise REDIS_ERR
+ * is returned. */
+int verifyDumpPayload(unsigned char *p, size_t len) {
+    unsigned char hash[20], *footer;
+    SHA1_CTX ctx;
+    uint16_t rdbver;
+
+    if (len < 10) return REDIS_ERR;
+    footer = p+(len-10);
+    rdbver = (footer[0] << 8) | footer[1];
+    if (rdbver != REDIS_RDB_VERSION) return REDIS_ERR;
+    SHA1Init(&ctx);
+    SHA1Update(&ctx,p,len-8);
+    SHA1Final(hash,&ctx);
+    return (memcmp(hash,footer+2,8) == 0) ? REDIS_OK : REDIS_ERR;
+}
+
+/* DUMP keyname
+ * DUMP is actually not used by Redis Cluster but it is the obvious
+ * complement of RESTORE and can be useful for different applications. */
+void dumpCommand(redisClient *c) {
+    robj *o, *dumpobj;
+    rio payload;
+
+    /* Check if the key is here. */
+    if ((o = lookupKeyRead(c->db,c->argv[1])) == NULL) {
+        addReply(c,shared.nullbulk);
+        return;
+    }
+
+    /* Create the DUMP encoded representation. */
+    createDumpPayload(&payload,o);
+
+    /* Transfer to the client */
+    dumpobj = createObject(REDIS_STRING,payload.io.buffer.ptr);
+    addReplyBulk(c,dumpobj);
+    decrRefCount(dumpobj);
+    return;
+}
+
 /* RESTORE key ttl serialized-value */
 void restoreCommand(redisClient *c) {
     long ttl;
@@ -1481,6 +1553,12 @@ void restoreCommand(redisClient *c) {
         return;
     }
 
+    /* Verify truncated SHA1 and RDB version. */
+    if (verifyDumpPayload(c->argv[3]->ptr,sdslen(c->argv[3]->ptr)) == REDIS_ERR) {
+        addReplyError(c,"DUMP payload version or checksum are wrong");
+        return;
+    }
+
     rioInitWithBuffer(&payload,c->argv[3]->ptr);
     if (((type = rdbLoadObjectType(&payload)) == -1) ||
         ((obj = rdbLoadObject(type,&payload)) == NULL))
@@ -1534,6 +1612,7 @@ void migrateCommand(redisClient *c) {
         return;
     }
 
+    /* Create RESTORE payload and generate the protocol to call the command. */
     rioInitWithBuffer(&cmd,sdsempty());
     redisAssertWithInfo(c,NULL,rioWriteBulkCount(&cmd,'*',2));
     redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"SELECT",6));
@@ -1547,11 +1626,10 @@ void migrateCommand(redisClient *c) {
     redisAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,(ttl == -1) ? 0 : ttl));
 
     /* Finally the last argument that is the serailized object payload
-     * in the form: <type><rdb-serialized-object>. */
-    rioInitWithBuffer(&payload,sdsempty());
-    redisAssertWithInfo(c,NULL,rdbSaveObjectType(&payload,o));
-    redisAssertWithInfo(c,NULL,rdbSaveObject(&payload,o) != -1);
-    redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,payload.io.buffer.ptr,sdslen(payload.io.buffer.ptr)));
+     * in the DUMP format. */
+    createDumpPayload(&payload,o);
+    redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,payload.io.buffer.ptr,
+                                sdslen(payload.io.buffer.ptr)));
     sdsfree(payload.io.buffer.ptr);
 
     /* Tranfer the query to the other node in 64K chunks. */
@@ -1619,32 +1697,6 @@ void migrateCommand(redisClient *c) {
     return;
 }
 
-/* DUMP keyname
- * DUMP is actually not used by Redis Cluster but it is the obvious
- * complement of RESTORE and can be useful for different applications. */
-void dumpCommand(redisClient *c) {
-    robj *o, *dumpobj;
-    rio payload;
-
-    /* Check if the key is here. */
-    if ((o = lookupKeyRead(c->db,c->argv[1])) == NULL) {
-        addReply(c,shared.nullbulk);
-        return;
-    }
-
-    /* Serialize the object in a RDB-like format. It consist of an object type
-     * byte followed by the serialized object. This is understood by RESTORE. */
-    rioInitWithBuffer(&payload,sdsempty());
-    redisAssertWithInfo(c,NULL,rdbSaveObjectType(&payload,o));
-    redisAssertWithInfo(c,NULL,rdbSaveObject(&payload,o));
-
-    /* Transfer to the client */
-    dumpobj = createObject(REDIS_STRING,payload.io.buffer.ptr);
-    addReplyBulk(c,dumpobj);
-    decrRefCount(dumpobj);
-    return;
-}
-
 /* The ASKING command is required after a -ASK redirection.
  * The client should issue ASKING before to actualy send the command to
  * the target instance. See the Redis Cluster specification for more