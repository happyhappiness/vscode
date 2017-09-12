@@ -10,21 +10,38 @@
 #define INTSET_ENC_INT32 (sizeof(int32_t))
 #define INTSET_ENC_INT64 (sizeof(int64_t))
 
-/* Accessors for each type of encoding */
-#define INTSET_VALUE_ENCODING(__val) (((__val) < INT32_MIN || (__val) > INT32_MAX) ? \
-    INTSET_ENC_INT64 : (((__val) < INT16_MIN || (__val) > INT16_MAX) ? \
-    INTSET_ENC_INT32 : INTSET_ENC_INT16))
-#define INTSET_GET_ENCODED(__is,__pos,__enc) ((__enc == INTSET_ENC_INT64) ? \
-    ((int64_t*)(__is)->contents)[__pos] : ((__enc == INTSET_ENC_INT32) ? \
-    ((int32_t*)(__is)->contents)[__pos] : ((int16_t*)(__is)->contents)[__pos]))
-#define INTSET_GET(__is,__pos) (INTSET_GET_ENCODED(__is,__pos,(__is)->encoding))
-#define INTSET_SET(__is,__pos,__val) { \
-    if ((__is)->encoding == INTSET_ENC_INT64) \
-        ((int64_t*)(__is)->contents)[__pos] = (__val); \
-    else if ((__is)->encoding == INTSET_ENC_INT32) \
-        ((int32_t*)(__is)->contents)[__pos] = (__val); \
-    else \
-        ((int16_t*)(__is)->contents)[__pos] = (__val); }
+/* Return the required encoding for the provided value. */
+static uint8_t _intsetValueEncoding(int64_t v) {
+    if (v < INT32_MIN || v > INT32_MAX)
+        return INTSET_ENC_INT64;
+    else if (v < INT16_MIN || v > INT16_MAX)
+        return INTSET_ENC_INT32;
+    return INTSET_ENC_INT16;
+}
+
+/* Return the value at pos, given an encoding. */
+static int64_t _intsetGetEncoded(intset *is, int pos, uint8_t enc) {
+    if (enc == INTSET_ENC_INT64)
+        return ((int64_t*)is->contents)[pos];
+    else if (enc == INTSET_ENC_INT32)
+        return ((int32_t*)is->contents)[pos];
+    return ((int16_t*)is->contents)[pos];
+}
+
+/* Return the value at pos, using the configured encoding. */
+static int64_t _intsetGet(intset *is, int pos) {
+    return _intsetGetEncoded(is,pos,is->encoding);
+}
+
+/* Set the value at pos, using the configured encoding. */
+static void _intsetSet(intset *is, int pos, int64_t value) {
+    if (is->encoding == INTSET_ENC_INT64)
+        ((int64_t*)is->contents)[pos] = value;
+    else if (is->encoding == INTSET_ENC_INT32)
+        ((int32_t*)is->contents)[pos] = value;
+    else
+        ((int16_t*)is->contents)[pos] = value;
+}
 
 /* Create an empty intset. */
 intset *intsetNew(void) {
@@ -51,7 +68,7 @@ static intset *intsetUpgrade(intset *is, uint8_t newenc, uint8_t extra, uint8_t
 
     /* Upgrade back-to-front so we don't overwrite values */
     while(length--)
-        INTSET_SET(is,length+offset,INTSET_GET_ENCODED(is,length,curenc));
+        _intsetSet(is,length+offset,_intsetGetEncoded(is,length,curenc));
     return is;
 }
 
@@ -70,18 +87,18 @@ static uint8_t intsetSearch(intset *is, int64_t value, uint32_t *pos) {
     } else {
         /* Check for the case where we know we cannot find the value,
          * but do know the insert position. */
-        if (value > INTSET_GET(is,is->length-1)) {
+        if (value > _intsetGet(is,is->length-1)) {
             if (pos) *pos = is->length;
             return 0;
-        } else if (value < INTSET_GET(is,0)) {
+        } else if (value < _intsetGet(is,0)) {
             if (pos) *pos = 0;
             return 0;
         }
     }
 
     while(max >= min) {
         mid = (min+max)/2;
-        cur = INTSET_GET(is,mid);
+        cur = _intsetGet(is,mid);
         if (value > cur) {
             min = mid+1;
         } else if (value < cur) {
@@ -121,7 +138,7 @@ static void intsetMoveTail(intset *is, uint32_t from, uint32_t to) {
 
 /* Insert an integer in the intset */
 intset *intsetAdd(intset *is, int64_t value, uint8_t *success) {
-    uint8_t valenc = INTSET_VALUE_ENCODING(value);
+    uint8_t valenc = _intsetValueEncoding(value);
     uint32_t pos, offset;
     if (success) *success = 1;
 
@@ -145,14 +162,14 @@ intset *intsetAdd(intset *is, int64_t value, uint8_t *success) {
         if (pos < is->length) intsetMoveTail(is,pos,pos+1);
     }
 
-    INTSET_SET(is,pos,value);
+    _intsetSet(is,pos,value);
     is->length++;
     return is;
 }
 
 /* Delete integer from intset */
 intset *intsetRemove(intset *is, int64_t value, uint8_t *success) {
-    uint8_t valenc = INTSET_VALUE_ENCODING(value);
+    uint8_t valenc = _intsetValueEncoding(value);
     uint32_t pos;
     if (success) *success = 0;
 
@@ -170,20 +187,20 @@ intset *intsetRemove(intset *is, int64_t value, uint8_t *success) {
 
 /* Determine whether a value belongs to this set */
 uint8_t intsetFind(intset *is, int64_t value) {
-    uint8_t valenc = INTSET_VALUE_ENCODING(value);
+    uint8_t valenc = _intsetValueEncoding(value);
     return valenc <= is->encoding && intsetSearch(is,value,NULL);
 }
 
 /* Return random member */
 int64_t intsetRandom(intset *is) {
-    return INTSET_GET(is,rand()%is->length);
+    return _intsetGet(is,rand()%is->length);
 }
 
 /* Sets the value to the value at the given position. When this position is
  * out of range the function returns 0, when in range it returns 1. */
 uint8_t intsetGet(intset *is, uint32_t pos, int64_t *value) {
     if (pos < is->length) {
-        *value = INTSET_GET(is,pos);
+        *value = _intsetGet(is,pos);
         return 1;
     }
     return 0;
@@ -200,7 +217,7 @@ uint32_t intsetLen(intset *is) {
 void intsetRepr(intset *is) {
     int i;
     for (i = 0; i < is->length; i++) {
-        printf("%lld\n", (uint64_t)INTSET_GET(is,i));
+        printf("%lld\n", (uint64_t)_intsetGet(is,i));
     }
     printf("\n");
 }
@@ -266,16 +283,16 @@ int main(int argc, char **argv) {
     sranddev();
 
     printf("Value encodings: "); {
-        assert(INTSET_VALUE_ENCODING(-32768) == INTSET_ENC_INT16);
-        assert(INTSET_VALUE_ENCODING(+32767) == INTSET_ENC_INT16);
-        assert(INTSET_VALUE_ENCODING(-32769) == INTSET_ENC_INT32);
-        assert(INTSET_VALUE_ENCODING(+32768) == INTSET_ENC_INT32);
-        assert(INTSET_VALUE_ENCODING(-2147483648) == INTSET_ENC_INT32);
-        assert(INTSET_VALUE_ENCODING(+2147483647) == INTSET_ENC_INT32);
-        assert(INTSET_VALUE_ENCODING(-2147483649) == INTSET_ENC_INT64);
-        assert(INTSET_VALUE_ENCODING(+2147483648) == INTSET_ENC_INT64);
-        assert(INTSET_VALUE_ENCODING(-9223372036854775808ull) == INTSET_ENC_INT64);
-        assert(INTSET_VALUE_ENCODING(+9223372036854775807ull) == INTSET_ENC_INT64);
+        assert(_intsetValueEncoding(-32768) == INTSET_ENC_INT16);
+        assert(_intsetValueEncoding(+32767) == INTSET_ENC_INT16);
+        assert(_intsetValueEncoding(-32769) == INTSET_ENC_INT32);
+        assert(_intsetValueEncoding(+32768) == INTSET_ENC_INT32);
+        assert(_intsetValueEncoding(-2147483648) == INTSET_ENC_INT32);
+        assert(_intsetValueEncoding(+2147483647) == INTSET_ENC_INT32);
+        assert(_intsetValueEncoding(-2147483649) == INTSET_ENC_INT64);
+        assert(_intsetValueEncoding(+2147483648) == INTSET_ENC_INT64);
+        assert(_intsetValueEncoding(-9223372036854775808ull) == INTSET_ENC_INT64);
+        assert(_intsetValueEncoding(+9223372036854775807ull) == INTSET_ENC_INT64);
         ok();
     }
 