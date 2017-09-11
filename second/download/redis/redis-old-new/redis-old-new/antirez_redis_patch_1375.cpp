@@ -20,6 +20,7 @@
 #define REDIS_LIST_ZIPLIST 10
 #define REDIS_SET_INTSET 11
 #define REDIS_ZSET_ZIPLIST 12
+#define REDIS_HASH_ZIPLIST 13
 
 /* Objects encoding. Some kind of objects like Strings and Hashes can be
  * internally represented in multiple ways. The 'encoding' field of the object
@@ -136,7 +137,7 @@ int processHeader() {
     }
 
     dump_version = (int)strtol(buf + 5, NULL, 10);
-    if (dump_version < 1 || dump_version > 2) {
+    if (dump_version < 1 || dump_version > 4) {
         ERROR("Unknown RDB format version: %d\n", dump_version);
     }
     return 1;
@@ -384,6 +385,7 @@ int loadPair(entry *e) {
     case REDIS_LIST_ZIPLIST:
     case REDIS_SET_INTSET:
     case REDIS_ZSET_ZIPLIST:
+    case REDIS_HASH_ZIPLIST:
         if (!processStringObject(NULL)) {
             SHIFT_ERROR(offset, "Error reading entry value");
             return 0;