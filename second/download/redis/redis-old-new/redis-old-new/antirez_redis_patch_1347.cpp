@@ -1,5 +1,5 @@
 #include "redis.h"
-#include "sha1.h"
+#include "endianconv.h"
 
 #include <arpa/inet.h>
 #include <fcntl.h>
@@ -1464,8 +1464,8 @@ void clusterCommand(redisClient *c) {
 /* Generates a DUMP-format representation of the object 'o', adding it to the
  * io stream pointed by 'rio'. This function can't fail. */
 void createDumpPayload(rio *payload, robj *o) {
-    unsigned char hash[20], buf[2];
-    SHA1_CTX ctx;
+    unsigned char buf[2];
+    uint64_t crc;
 
     /* Serialize the object in a RDB-like format. It consist of an object type
      * byte followed by the serialized object. This is understood by RESTORE. */
@@ -1474,47 +1474,45 @@ void createDumpPayload(rio *payload, robj *o) {
     redisAssert(rdbSaveObject(payload,o));
 
     /* Write the footer, this is how it looks like:
-     * ----------------+---------------------+--------------+
-     * ... RDB payload | 2 bytes RDB version | 8 bytes SHA1 |
-     * ----------------+---------------------+--------------+
-     * The SHA1 is just 8 bytes of truncated SHA1 of everything excluding itself.
-     * The 2 bytes RDB version is a little endian unsigned integer.  */
+     * ----------------+---------------------+---------------+
+     * ... RDB payload | 2 bytes RDB version | 8 bytes CRC64 |
+     * ----------------+---------------------+---------------+
+     * RDB version and CRC are both in little endian.
+     */
 
     /* RDB version */
     buf[0] = REDIS_RDB_VERSION & 0xff;
     buf[1] = (REDIS_RDB_VERSION >> 8) & 0xff;
     payload->io.buffer.ptr = sdscatlen(payload->io.buffer.ptr,buf,2);
 
-    /* Truncated SHA1 */
-    SHA1Init(&ctx);
-    SHA1Update(&ctx,(unsigned char*)payload->io.buffer.ptr,
-                    sdslen(payload->io.buffer.ptr));
-    SHA1Final(hash,&ctx);
-    payload->io.buffer.ptr = sdscatlen(payload->io.buffer.ptr,hash,8);
+    /* CRC64 */
+    crc = crc64((unsigned char*)payload->io.buffer.ptr,
+                sdslen(payload->io.buffer.ptr));
+    memrev64ifbe(&crc);
+    payload->io.buffer.ptr = sdscatlen(payload->io.buffer.ptr,&crc,8);
 }
 
 /* Verify that the RDB version of the dump payload matches the one of this Redis
- * instance and that the truncated SHA1 is ok.
+ * instance and that the checksum is ok.
  * If the DUMP payload looks valid REDIS_OK is returned, otherwise REDIS_ERR
  * is returned. */
 int verifyDumpPayload(unsigned char *p, size_t len) {
-    unsigned char hash[20], *footer;
-    SHA1_CTX ctx;
+    unsigned char *footer;
     uint16_t rdbver;
+    uint64_t crc;
 
-    /* At least 2 bytes of RDB version and 8 of truncated SHA should be present. */
+    /* At least 2 bytes of RDB version and 8 of CRC64 should be present. */
     if (len < 10) return REDIS_ERR;
     footer = p+(len-10);
 
     /* Verify RDB version */
     rdbver = (footer[1] << 8) | footer[0];
     if (rdbver != REDIS_RDB_VERSION) return REDIS_ERR;
 
-    /* Verify truncated SHA1 */
-    SHA1Init(&ctx);
-    SHA1Update(&ctx,p,len-8);
-    SHA1Final(hash,&ctx);
-    return (memcmp(hash,footer+2,8) == 0) ? REDIS_OK : REDIS_ERR;
+    /* Verify CRC64 */
+    crc = crc64(p,len-8);
+    memrev64ifbe(&crc);
+    return (memcmp(&crc,footer+2,8) == 0) ? REDIS_OK : REDIS_ERR;
 }
 
 /* DUMP keyname
@@ -1561,7 +1559,7 @@ void restoreCommand(redisClient *c) {
         return;
     }
 
-    /* Verify truncated SHA1 and RDB version. */
+    /* Verify RDB version and data checksum. */
     if (verifyDumpPayload(c->argv[3]->ptr,sdslen(c->argv[3]->ptr)) == REDIS_ERR) {
         addReplyError(c,"DUMP payload version or checksum are wrong");
         return;