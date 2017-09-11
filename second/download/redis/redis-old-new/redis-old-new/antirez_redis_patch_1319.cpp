@@ -52,14 +52,21 @@
  *      String value with length less than or equal to 16383 bytes (14 bits).
  * |10______|qqqqqqqq|rrrrrrrr|ssssssss|tttttttt| - 5 bytes
  *      String value with length greater than or equal to 16384 bytes.
- * |1100____| - 1 byte
+ * |11000000| - 1 byte
  *      Integer encoded as int16_t (2 bytes).
- * |1101____| - 1 byte
+ * |11010000| - 1 byte
  *      Integer encoded as int32_t (4 bytes).
- * |1110____| - 1 byte
+ * |11100000| - 1 byte
  *      Integer encoded as int64_t (8 bytes).
- * |1111____| - 1 byte
+ * |11110000| - 1 byte
  *      Integer encoded as 24 bit signed (3 bytes).
+ * |11111110| - 1 byte
+ *      Integer encoded as 8 bit signed (1 byte).
+ * |1111xxxx| - (with xxxx between 0000 and 1101) immediate 4 bit integer.
+ *      Unsigned integer from 0 to 12. The encoded value is actually from
+ *      1 to 13 because 0000 and 1111 can not be used, so 1 should be
+ *      subtracted from the encoded 4 bit value to obtain the right value.
+ * |11111111| - End of ziplist.
  *
  * All the integers are represented in little endian byte order.
  */
@@ -79,15 +86,21 @@
 #define ZIP_BIGLEN 254
 
 /* Different encoding/length possibilities */
-#define ZIP_STR_MASK (0xc0)
-#define ZIP_INT_MASK (0x30)
+#define ZIP_STR_MASK 0xc0
+#define ZIP_INT_MASK 0x30
 #define ZIP_STR_06B (0 << 6)
 #define ZIP_STR_14B (1 << 6)
 #define ZIP_STR_32B (2 << 6)
 #define ZIP_INT_16B (0xc0 | 0<<4)
 #define ZIP_INT_32B (0xc0 | 1<<4)
 #define ZIP_INT_64B (0xc0 | 2<<4)
 #define ZIP_INT_24B (0xc0 | 3<<4)
+#define ZIP_INT_8B 0xfe
+/* 4 bit integer immediate encoding */
+#define ZIP_INT_IMM_MASK 0x0f
+#define ZIP_INT_IMM_MIN 0xf1    /* 11110001 */
+#define ZIP_INT_IMM_MAX 0xfd    /* 11111101 */
+#define ZIP_INT_IMM_VAL(v) (v & ZIP_INT_IMM_MASK)
 
 #define INT24_MAX 0x7fffff
 #define INT24_MIN (-INT24_MAX - 1)
@@ -119,21 +132,22 @@ typedef struct zlentry {
     unsigned char *p;
 } zlentry;
 
-#define ZIP_ENTRY_ENCODING(ptr, encoding) do {                                 \
-    (encoding) = (ptr[0]) & (ZIP_STR_MASK | ZIP_INT_MASK);                     \
-    if (((encoding) & ZIP_STR_MASK) < ZIP_STR_MASK) {                          \
-        /* String encoding: 2 MSBs */                                          \
-        (encoding) &= ZIP_STR_MASK;                                            \
-    }                                                                          \
+/* Extract the encoding from the byte pointed by 'ptr' and set it into
+ * 'encoding'. */
+#define ZIP_ENTRY_ENCODING(ptr, encoding) do {  \
+    (encoding) = (ptr[0]); \
+    if ((encoding) < ZIP_STR_MASK) (encoding) &= ZIP_STR_MASK; \
 } while(0)
 
 /* Return bytes needed to store integer encoded by 'encoding' */
 static unsigned int zipIntSize(unsigned char encoding) {
     switch(encoding) {
-    case ZIP_INT_16B: return sizeof(int16_t);
-    case ZIP_INT_24B: return sizeof(int32_t)-sizeof(int8_t);
-    case ZIP_INT_32B: return sizeof(int32_t);
-    case ZIP_INT_64B: return sizeof(int64_t);
+    case ZIP_INT_8B:  return 1;
+    case ZIP_INT_16B: return 2;
+    case ZIP_INT_24B: return 3;
+    case ZIP_INT_32B: return 4;
+    case ZIP_INT_64B: return 8;
+    default: return 0; /* 4 bit immediate */
     }
     assert(NULL);
     return 0;
@@ -278,7 +292,11 @@ static int zipTryEncoding(unsigned char *entry, unsigned int entrylen, long long
     if (string2ll((char*)entry,entrylen,&value)) {
         /* Great, the string can be encoded. Check what's the smallest
          * of our encoding types that can hold this value. */
-        if (value >= INT16_MIN && value <= INT16_MAX) {
+        if (value >= 0 && value <= 12) {
+            *encoding = ZIP_INT_IMM_MIN+value;
+        } else if (value >= INT8_MIN && value <= INT8_MAX) {
+            *encoding = ZIP_INT_8B;
+        } else if (value >= INT16_MIN && value <= INT16_MAX) {
             *encoding = ZIP_INT_16B;
         } else if (value >= INT24_MIN && value <= INT24_MAX) {
             *encoding = ZIP_INT_24B;
@@ -298,7 +316,9 @@ static void zipSaveInteger(unsigned char *p, int64_t value, unsigned char encodi
     int16_t i16;
     int32_t i32;
     int64_t i64;
-    if (encoding == ZIP_INT_16B) {
+    if (encoding == ZIP_INT_8B) {
+        ((char*)p)[0] = (char)value;
+    } else if (encoding == ZIP_INT_16B) {
         i16 = value;
         memcpy(p,&i16,sizeof(i16));
         memrev16ifbe(p);
@@ -314,6 +334,8 @@ static void zipSaveInteger(unsigned char *p, int64_t value, unsigned char encodi
         i64 = value;
         memcpy(p,&i64,sizeof(i64));
         memrev64ifbe(p);
+    } else if (encoding >= ZIP_INT_IMM_MIN && encoding <= ZIP_INT_IMM_MAX) {
+        /* Nothing to do, the value is stored in the encoding itself. */
     } else {
         assert(NULL);
     }
@@ -324,7 +346,10 @@ static int64_t zipLoadInteger(unsigned char *p, unsigned char encoding) {
     int16_t i16;
     int32_t i32;
     int64_t i64, ret = 0;
-    if (encoding == ZIP_INT_16B) {
+    printf("%02x\n", encoding);
+    if (encoding == ZIP_INT_8B) {
+        ret = ((char*)p)[0];
+    } else if (encoding == ZIP_INT_16B) {
         memcpy(&i16,p,sizeof(i16));
         memrev16ifbe(&i16);
         ret = i16;
@@ -341,6 +366,8 @@ static int64_t zipLoadInteger(unsigned char *p, unsigned char encoding) {
         memcpy(&i64,p,sizeof(i64));
         memrev64ifbe(&i64);
         ret = i64;
+    } else if (encoding >= ZIP_INT_IMM_MIN && encoding <= ZIP_INT_IMM_MAX) {
+        ret = (encoding & ZIP_INT_IMM_MASK)-1;
     } else {
         assert(NULL);
     }