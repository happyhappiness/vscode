@@ -171,7 +171,7 @@ static int processTime(int type) {
     return 0;
 }
 
-static uint32_t loadLength(int *isencoded) {
+static uint64_t loadLength(int *isencoded) {
     unsigned char buf[2];
     uint32_t len;
     int type;
@@ -190,10 +190,16 @@ static uint32_t loadLength(int *isencoded) {
         /* Read a 14 bit len */
         if (!readBytes(buf+1,1)) return RDB_LENERR;
         return ((buf[0] & 0x3F) << 8) | buf[1];
-    } else {
+    } else if (buf[0] == RDB_32BITLEN) {
         /* Read a 32 bit len */
         if (!readBytes(&len, 4)) return RDB_LENERR;
-        return (unsigned int)ntohl(len);
+        return ntohl(len);
+    } else if (buf[0] == RDB_64BITLEN) {
+        /* Read a 64 bit len */
+        if (!readBytes(&len, 8)) return RDB_LENERR;
+        return ntohu64(len);
+    } else {
+        return RDB_LENERR;
     }
 }
 
@@ -230,7 +236,7 @@ static char *loadIntegerObject(int enctype) {
 }
 
 static char* loadLzfStringObject() {
-    unsigned int slen, clen;
+    uint64_t slen, clen;
     char *c, *s;
 
     if ((clen = loadLength(NULL)) == RDB_LENERR) return NULL;
@@ -254,9 +260,9 @@ static char* loadLzfStringObject() {
 
 /* returns NULL when not processable, char* when valid */
 static char* loadStringObject() {
-    uint32_t offset = CURR_OFFSET;
+    uint64_t offset = CURR_OFFSET;
+    uint64_t len;
     int isencoded;
-    uint32_t len;
 
     len = loadLength(&isencoded);
     if (isencoded) {
@@ -269,7 +275,7 @@ static char* loadStringObject() {
             return loadLzfStringObject();
         default:
             /* unknown encoding */
-            SHIFT_ERROR(offset, "Unknown string encoding (0x%02x)", len);
+            SHIFT_ERROR(offset, "Unknown string encoding (0x%02llx)", len);
             return NULL;
         }
     }
@@ -344,8 +350,8 @@ static int processDoubleValue(double** store) {
 }
 
 static int loadPair(entry *e) {
-    uint32_t offset = CURR_OFFSET;
-    uint32_t i;
+    uint64_t offset = CURR_OFFSET;
+    uint64_t i;
 
     /* read key first */
     char *key;
@@ -356,7 +362,7 @@ static int loadPair(entry *e) {
         return 0;
     }
 
-    uint32_t length = 0;
+    uint64_t length = 0;
     if (e->type == RDB_TYPE_LIST ||
         e->type == RDB_TYPE_SET  ||
         e->type == RDB_TYPE_ZSET ||
@@ -384,7 +390,7 @@ static int loadPair(entry *e) {
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element at index %d (length: %d)", i, length);
+                SHIFT_ERROR(offset, "Error reading element at index %llu (length: %llu)", i, length);
                 return 0;
             }
         }
@@ -393,12 +399,12 @@ static int loadPair(entry *e) {
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element key at index %d (length: %d)", i, length);
+                SHIFT_ERROR(offset, "Error reading element key at index %llu (length: %llu)", i, length);
                 return 0;
             }
             offset = CURR_OFFSET;
             if (!processDoubleValue(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element value at index %d (length: %d)", i, length);
+                SHIFT_ERROR(offset, "Error reading element value at index %llu (length: %llu)", i, length);
                 return 0;
             }
         }
@@ -407,12 +413,12 @@ static int loadPair(entry *e) {
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element key at index %d (length: %d)", i, length);
+                SHIFT_ERROR(offset, "Error reading element key at index %llu (length: %llu)", i, length);
                 return 0;
             }
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element value at index %d (length: %d)", i, length);
+                SHIFT_ERROR(offset, "Error reading element value at index %llu (length: %llu)", i, length);
                 return 0;
             }
         }
@@ -428,7 +434,7 @@ static int loadPair(entry *e) {
 
 static entry loadEntry() {
     entry e = { NULL, -1, 0 };
-    uint32_t length, offset[4];
+    uint64_t length, offset[4];
 
     /* reset error container */
     errors.level = 0;
@@ -445,7 +451,7 @@ static entry loadEntry() {
             return e;
         }
         if (length > 63) {
-            SHIFT_ERROR(offset[1], "Database number out of range (%d)", length);
+            SHIFT_ERROR(offset[1], "Database number out of range (%llu)", length);
             return e;
         }
     } else if (e.type == RDB_OPCODE_EOF) {