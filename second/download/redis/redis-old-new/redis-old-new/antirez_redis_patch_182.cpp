@@ -41,22 +41,29 @@
 #include <sys/stat.h>
 #include <sys/param.h>
 
-#define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);
+#define rdbExitReportCorruptRDB(...) rdbCheckThenExit(__LINE__,__VA_ARGS__)
 
 extern int rdbCheckMode;
 void rdbCheckError(const char *fmt, ...);
 void rdbCheckSetError(const char *fmt, ...);
 
-void rdbCheckThenExit(char *reason, int where) {
-     if (!rdbCheckMode) {
-        serverLog(LL_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
-            "Running 'redis-check-rdb %s'",
-            where, reason, server.rdb_filename);
+void rdbCheckThenExit(int linenum, char *reason, ...) {
+    va_list ap;
+    char msg[1024];
+    int len;
+
+    len = snprintf(msg,sizeof(msg),
+        "Internal error in RDB reading function at rdb.c:%d -> ", linenum);
+    va_start(ap,reason);
+    vsnprintf(msg+len,sizeof(msg)-len,reason,ap);
+    va_end(ap);
+
+    if (!rdbCheckMode) {
+        serverLog(LL_WARNING, "%s", msg);
         char *argv[2] = {"",server.rdb_filename};
         redis_check_rdb_main(2,argv);
     } else {
-        rdbCheckError("Internal error in RDB reading function at rdb.c:%d (%s)",
-            where, reason);
+        rdbCheckError("%s",msg);
     }
     exit(1);
 }
@@ -172,7 +179,8 @@ int rdbLoadLenByRef(rio *rdb, int *isencoded, uint64_t *lenptr) {
         if (rioRead(rdb,&len,8) == 0) return -1;
         *lenptr = ntohu64(len);
     } else {
-        rdbExitReportCorruptRDB("Unknown length encoding in rdbLoadLen()");
+        rdbExitReportCorruptRDB(
+            "Unknown length encoding %d in rdbLoadLen()",type);
         return -1; /* Never reached. */
     }
     return 0;
@@ -240,7 +248,7 @@ void *rdbLoadIntegerObject(rio *rdb, int enctype, int flags, size_t *lenptr) {
         val = (int32_t)v;
     } else {
         val = 0; /* anti-warning */
-        rdbExitReportCorruptRDB("Unknown RDB integer encoding type");
+        rdbExitReportCorruptRDB("Unknown RDB integer encoding type %d",enctype);
     }
     if (plain || sds) {
         char buf[LONG_STR_SIZE], *p;
@@ -457,7 +465,7 @@ void *rdbGenericLoadStringObject(rio *rdb, int flags, size_t *lenptr) {
         case RDB_ENC_LZF:
             return rdbLoadLzfStringObject(rdb,flags,lenptr);
         default:
-            rdbExitReportCorruptRDB("Unknown RDB encoding type");
+            rdbExitReportCorruptRDB("Unknown RDB string encoding type %d",len);
         }
     }
 
@@ -1288,7 +1296,7 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                     hashTypeConvert(o, OBJ_ENCODING_HT);
                 break;
             default:
-                rdbExitReportCorruptRDB("Unknown encoding");
+                rdbExitReportCorruptRDB("Unknown RDB encoding type %d",rdbtype);
                 break;
         }
     } else if (rdbtype == RDB_TYPE_MODULE) {
@@ -1313,7 +1321,7 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
         }
         o = createModuleObject(mt,ptr);
     } else {
-        rdbExitReportCorruptRDB("Unknown object type");
+        rdbExitReportCorruptRDB("Unknown RDB encoding type %d",rdbtype);
     }
     return o;
 }