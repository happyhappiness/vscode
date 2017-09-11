@@ -44,6 +44,16 @@
 #define RDB_LOAD_ENC    (1<<0)
 #define RDB_LOAD_PLAIN  (1<<1)
 
+#define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);
+
+void rdbCheckThenExit(char *reason, int where) {
+    redisLog(REDIS_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
+        "Running 'redis-check-rdb --dbfilename %s'",
+        where, reason, server.rdb_filename);
+    redis_check_rdb(server.rdb_filename);
+    exit(1);
+}
+
 static int rdbWriteRaw(rio *rdb, void *p, size_t len) {
     if (rdb && rioWrite(rdb,p,len) == 0)
         return -1;
@@ -188,7 +198,7 @@ void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags) {
         val = (int32_t)v;
     } else {
         val = 0; /* anti-warning */
-        redisPanic("Unknown RDB integer encoding type");
+        rdbExitReportCorruptRDB("Unknown RDB integer encoding type");
     }
     if (plain) {
         char buf[REDIS_LONGSTR_SIZE], *p;
@@ -394,7 +404,7 @@ void *rdbGenericLoadStringObject(rio *rdb, int flags) {
         case REDIS_RDB_ENC_LZF:
             return rdbLoadLzfStringObject(rdb,flags);
         default:
-            redisPanic("Unknown RDB encoding type");
+            rdbExitReportCorruptRDB("Unknown RDB encoding type");
         }
     }
 
@@ -923,7 +933,7 @@ void rdbRemoveTempFile(pid_t childpid) {
 /* Load a Redis object of the specified type from the specified file.
  * On success a newly allocated object is returned, otherwise NULL. */
 robj *rdbLoadObject(int rdbtype, rio *rdb) {
-    robj *o, *ele, *dec;
+    robj *o = NULL, *ele, *dec;
     size_t len;
     unsigned int i;
 
@@ -1078,7 +1088,9 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
 
             /* Add pair to hash table */
             ret = dictAdd((dict*)o->ptr, field, value);
-            redisAssert(ret == DICT_OK);
+            if (ret == DICT_ERR) {
+                rdbExitReportCorruptRDB("Duplicate keys detected");
+            }
         }
 
         /* All pairs should be read by now */
@@ -1164,11 +1176,11 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                     hashTypeConvert(o, REDIS_ENCODING_HT);
                 break;
             default:
-                redisPanic("Unknown encoding");
+                rdbExitReportCorruptRDB("Unknown encoding");
                 break;
         }
     } else {
-        redisPanic("Unknown object type");
+        rdbExitReportCorruptRDB("Unknown object type");
     }
     return o;
 }