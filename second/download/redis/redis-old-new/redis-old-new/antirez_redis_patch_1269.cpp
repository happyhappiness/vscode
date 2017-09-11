@@ -31,6 +31,7 @@
 #define REDIS_ENCODING_HT 3     /* Encoded as an hash table */
 
 /* Object types only used for dumping to disk */
+#define REDIS_EXPIRETIME_MS 252
 #define REDIS_EXPIRETIME 253
 #define REDIS_SELECTDB 254
 #define REDIS_EOF 255
@@ -111,6 +112,16 @@ static char types[256][16];
 /* Prototypes */
 uint64_t crc64(uint64_t crc, const unsigned char *s, uint64_t l);
 
+/* Return true if 't' is a valid object type. */
+int checkType(unsigned char t) {
+    /* In case a new object type is added, update the following 
+     * condition as necessary. */
+    return
+        (t >= REDIS_HASH_ZIPMAP && t <= REDIS_HASH_ZIPLIST) ||
+        t <= REDIS_HASH ||
+        t >= REDIS_EXPIRETIME_MS;
+}
+
 /* when number of bytes to read is negative, do a peek */
 int readBytes(void *target, long num) {
     char peek = (num < 0) ? 1 : 0;
@@ -152,7 +163,7 @@ int loadType(entry *e) {
     /* this byte needs to qualify as type */
     unsigned char t;
     if (readBytes(&t, 1)) {
-        if (t <= 4 || (t >=9 && t <= 12) || t >= 253) {
+        if (checkType(t)) {
             e->type = t;
             return 1;
         } else {
@@ -168,16 +179,18 @@ int loadType(entry *e) {
 
 int peekType() {
     unsigned char t;
-    if (readBytes(&t, -1) && (t <= 4 || (t >=9 && t <= 12) || t >= 253))
+    if (readBytes(&t, -1) && (checkType(t)))
         return t;
     return -1;
 }
 
 /* discard time, just consume the bytes */
-int processTime() {
+int processTime(int type) {
     uint32_t offset = CURR_OFFSET;
-    unsigned char t[4];
-    if (readBytes(t, 4)) {
+    unsigned char t[8];
+    int timelen = (type == REDIS_EXPIRETIME_MS) ? 8 : 4;
+
+    if (readBytes(t,timelen)) {
         return 1;
     } else {
         SHIFT_ERROR(offset, "Could not read time");
@@ -472,8 +485,9 @@ entry loadEntry() {
         return e;
     } else {
         /* optionally consume expire */
-        if (e.type == REDIS_EXPIRETIME) {
-            if (!processTime()) return e;
+        if (e.type == REDIS_EXPIRETIME || 
+            e.type == REDIS_EXPIRETIME_MS) {
+            if (!processTime(e.type)) return e;
             if (!loadType(&e)) return e;
         }
 