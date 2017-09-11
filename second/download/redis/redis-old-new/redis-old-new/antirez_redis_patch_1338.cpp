@@ -1,6 +1,7 @@
 #include "redis.h"
 #include "lzf.h"    /* LZF compression library */
 #include "zipmap.h"
+#include "endianconv.h"
 
 #include <math.h>
 #include <sys/types.h>
@@ -602,6 +603,7 @@ int rdbSave(char *filename) {
     long long now = mstime();
     FILE *fp;
     rio rdb;
+    uint64_t cksum;
 
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
@@ -612,6 +614,7 @@ int rdbSave(char *filename) {
     }
 
     rioInitWithFile(&rdb,fp);
+    rdb.update_cksum = rioGenericUpdateChecksum;
     snprintf(magic,sizeof(magic),"REDIS%04d",REDIS_RDB_VERSION);
     if (rdbWriteRaw(&rdb,magic,9) == -1) goto werr;
 
@@ -641,9 +644,16 @@ int rdbSave(char *filename) {
         }
         dictReleaseIterator(di);
     }
+    di = NULL; /* So that we don't release it again on error. */
+
     /* EOF opcode */
     if (rdbSaveType(&rdb,REDIS_RDB_OPCODE_EOF) == -1) goto werr;
 
+    /* CRC64 checksum */
+    cksum = rdb.cksum;
+    memrev64ifbe(&cksum);
+    rioWrite(&rdb,&cksum,8);
+
     /* Make sure data will not remain on the OS's output buffers */
     fflush(fp);
     fsync(fileno(fp));
@@ -1016,6 +1026,7 @@ int rdbLoad(char *filename) {
         return REDIS_ERR;
     }
     rioInitWithFile(&rdb,fp);
+    rdb.update_cksum = rioGenericUpdateChecksum;
     if (rioRead(&rdb,buf,9) == 0) goto eoferr;
     buf[9] = '\0';
     if (memcmp(buf,"REDIS",5) != 0) {
@@ -1025,7 +1036,7 @@ int rdbLoad(char *filename) {
         return REDIS_ERR;
     }
     rdbver = atoi(buf+5);
-    if (rdbver < 1 || rdbver > 4) {
+    if (rdbver < 1 || rdbver > 5) {
         fclose(fp);
         redisLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
         errno = EINVAL;
@@ -1096,6 +1107,18 @@ int rdbLoad(char *filename) {
 
         decrRefCount(key);
     }
+    /* Verify the checksum if RDB version is >= 5 */
+    if (rdbver >= 5) {
+        uint64_t cksum, expected = rdb.cksum;
+
+        if (rioRead(&rdb,&cksum,8) == 0) goto eoferr;
+        memrev64ifbe(&cksum);
+        if (cksum != expected) {
+            redisLog(REDIS_WARNING,"Wrong RDB checksum. Aborting now.");
+            exit(1);
+        }
+    }
+
     fclose(fp);
     stopLoading();
     return REDIS_OK;