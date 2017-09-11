@@ -16,6 +16,10 @@
 #define REDIS_SET 2
 #define REDIS_ZSET 3
 #define REDIS_HASH 4
+#define REDIS_HASH_ZIPMAP 9
+#define REDIS_LIST_ZIPLIST 10
+#define REDIS_SET_INTSET 11
+#define REDIS_ZSET_ZIPLIST 12
 
 /* Objects encoding. Some kind of objects like Strings and Hashes can be
  * internally represented in multiple ways. The 'encoding' field of the object
@@ -132,7 +136,7 @@ int processHeader() {
     }
 
     dump_version = (int)strtol(buf + 5, NULL, 10);
-    if (dump_version != 1) {
+    if (dump_version < 1 || dump_version > 2) {
         ERROR("Unknown RDB format version: %d\n", dump_version);
     }
     return 1;
@@ -144,7 +148,7 @@ int loadType(entry *e) {
     /* this byte needs to qualify as type */
     unsigned char t;
     if (readBytes(&t, 1)) {
-        if (t <= 4 || t >= 253) {
+        if (t <= 4 || (t >=9 && t <= 12) || t >= 253) {
             e->type = t;
             return 1;
         } else {
@@ -160,7 +164,8 @@ int loadType(entry *e) {
 
 int peekType() {
     unsigned char t;
-    if (readBytes(&t, -1) && (t <= 4 || t >= 253)) return t;
+    if (readBytes(&t, -1) && (t <= 4 || (t >=9 && t <= 12) || t >= 253))
+        return t;
     return -1;
 }
 
@@ -375,6 +380,10 @@ int loadPair(entry *e) {
 
     switch(e->type) {
     case REDIS_STRING:
+    case REDIS_HASH_ZIPMAP:
+    case REDIS_LIST_ZIPLIST:
+    case REDIS_SET_INTSET:
+    case REDIS_ZSET_ZIPLIST:
         if (!processStringObject(NULL)) {
             SHIFT_ERROR(offset, "Error reading entry value");
             return 0;