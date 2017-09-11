@@ -44,15 +44,17 @@ static int64_t _intsetGetEncoded(intset *is, int pos, uint8_t enc) {
 
 /* Return the value at pos, using the configured encoding. */
 static int64_t _intsetGet(intset *is, int pos) {
-    return _intsetGetEncoded(is,pos,is->encoding);
+    return _intsetGetEncoded(is,pos,intrev32ifbe(is->encoding));
 }
 
 /* Set the value at pos, using the configured encoding. */
 static void _intsetSet(intset *is, int pos, int64_t value) {
-    if (is->encoding == INTSET_ENC_INT64) {
+    uint32_t encoding = intrev32ifbe(is->encoding);
+
+    if (encoding == INTSET_ENC_INT64) {
         ((int64_t*)is->contents)[pos] = value;
         memrev64ifbe(((int64_t*)is->contents)+pos);
-    } else if (is->encoding == INTSET_ENC_INT32) {
+    } else if (encoding == INTSET_ENC_INT32) {
         ((int32_t*)is->contents)[pos] = value;
         memrev32ifbe(((int32_t*)is->contents)+pos);
     } else {
@@ -64,14 +66,14 @@ static void _intsetSet(intset *is, int pos, int64_t value) {
 /* Create an empty intset. */
 intset *intsetNew(void) {
     intset *is = zmalloc(sizeof(intset));
-    is->encoding = INTSET_ENC_INT16;
+    is->encoding = intrev32ifbe(INTSET_ENC_INT16);
     is->length = 0;
     return is;
 }
 
 /* Resize the intset */
 static intset *intsetResize(intset *is, uint32_t len) {
-    uint32_t size = len*is->encoding;
+    uint32_t size = len*intrev32ifbe(is->encoding);
     is = zrealloc(is,sizeof(intset)+size);
     return is;
 }
@@ -81,18 +83,18 @@ static intset *intsetResize(intset *is, uint32_t len) {
  * the value is not present in the intset and sets "pos" to the position
  * where "value" can be inserted. */
 static uint8_t intsetSearch(intset *is, int64_t value, uint32_t *pos) {
-    int min = 0, max = is->length-1, mid = -1;
+    int min = 0, max = intrev32ifbe(is->length)-1, mid = -1;
     int64_t cur = -1;
 
     /* The value can never be found when the set is empty */
-    if (is->length == 0) {
+    if (intrev32ifbe(is->length) == 0) {
         if (pos) *pos = 0;
         return 0;
     } else {
         /* Check for the case where we know we cannot find the value,
          * but do know the insert position. */
-        if (value > _intsetGet(is,is->length-1)) {
-            if (pos) *pos = is->length;
+        if (value > _intsetGet(is,intrev32ifbe(is->length)-1)) {
+            if (pos) *pos = intrev32ifbe(is->length);
             return 0;
         } else if (value < _intsetGet(is,0)) {
             if (pos) *pos = 0;
@@ -123,14 +125,14 @@ static uint8_t intsetSearch(intset *is, int64_t value, uint32_t *pos) {
 
 /* Upgrades the intset to a larger encoding and inserts the given integer. */
 static intset *intsetUpgradeAndAdd(intset *is, int64_t value) {
-    uint8_t curenc = is->encoding;
+    uint8_t curenc = intrev32ifbe(is->encoding);
     uint8_t newenc = _intsetValueEncoding(value);
-    int length = is->length;
+    int length = intrev32ifbe(is->length);
     int prepend = value < 0 ? 1 : 0;
 
     /* First set new encoding and resize */
-    is->encoding = newenc;
-    is = intsetResize(is,is->length+1);
+    is->encoding = intrev32ifbe(newenc);
+    is = intsetResize(is,intrev32ifbe(is->length)+1);
 
     /* Upgrade back-to-front so we don't overwrite values.
      * Note that the "prepend" variable is used to make sure we have an empty
@@ -142,19 +144,21 @@ static intset *intsetUpgradeAndAdd(intset *is, int64_t value) {
     if (prepend)
         _intsetSet(is,0,value);
     else
-        _intsetSet(is,is->length,value);
-    is->length++;
+        _intsetSet(is,intrev32ifbe(is->length),value);
+    is->length = intrev32ifbe(intrev32ifbe(is->length)+1);
     return is;
 }
 
 static void intsetMoveTail(intset *is, uint32_t from, uint32_t to) {
     void *src, *dst;
-    uint32_t bytes = is->length-from;
-    if (is->encoding == INTSET_ENC_INT64) {
+    uint32_t bytes = intrev32ifbe(is->length)-from;
+    uint32_t encoding = intrev32ifbe(is->encoding);
+
+    if (encoding == INTSET_ENC_INT64) {
         src = (int64_t*)is->contents+from;
         dst = (int64_t*)is->contents+to;
         bytes *= sizeof(int64_t);
-    } else if (is->encoding == INTSET_ENC_INT32) {
+    } else if (encoding == INTSET_ENC_INT32) {
         src = (int32_t*)is->contents+from;
         dst = (int32_t*)is->contents+to;
         bytes *= sizeof(int32_t);
@@ -175,7 +179,7 @@ intset *intsetAdd(intset *is, int64_t value, uint8_t *success) {
     /* Upgrade encoding if necessary. If we need to upgrade, we know that
      * this value should be either appended (if > 0) or prepended (if < 0),
      * because it lies outside the range of existing values. */
-    if (valenc > is->encoding) {
+    if (valenc > intrev32ifbe(is->encoding)) {
         /* This always succeeds, so we don't need to curry *success. */
         return intsetUpgradeAndAdd(is,value);
     } else {
@@ -187,12 +191,12 @@ intset *intsetAdd(intset *is, int64_t value, uint8_t *success) {
             return is;
         }
 
-        is = intsetResize(is,is->length+1);
-        if (pos < is->length) intsetMoveTail(is,pos,pos+1);
+        is = intsetResize(is,intrev32ifbe(is->length)+1);
+        if (pos < intrev32ifbe(is->length)) intsetMoveTail(is,pos,pos+1);
     }
 
     _intsetSet(is,pos,value);
-    is->length++;
+    is->length = intrev32ifbe(intrev32ifbe(is->length)+1);
     return is;
 }
 
@@ -202,33 +206,35 @@ intset *intsetRemove(intset *is, int64_t value, int *success) {
     uint32_t pos;
     if (success) *success = 0;
 
-    if (valenc <= is->encoding && intsetSearch(is,value,&pos)) {
+    if (valenc <= intrev32ifbe(is->encoding) && intsetSearch(is,value,&pos)) {
+        uint32_t len = intrev32ifbe(is->length);
+
         /* We know we can delete */
         if (success) *success = 1;
 
         /* Overwrite value with tail and update length */
-        if (pos < (is->length-1)) intsetMoveTail(is,pos+1,pos);
-        is = intsetResize(is,is->length-1);
-        is->length--;
+        if (pos < (len-1)) intsetMoveTail(is,pos+1,pos);
+        is = intsetResize(is,len-1);
+        is->length = intrev32ifbe(len-1);
     }
     return is;
 }
 
 /* Determine whether a value belongs to this set */
 uint8_t intsetFind(intset *is, int64_t value) {
     uint8_t valenc = _intsetValueEncoding(value);
-    return valenc <= is->encoding && intsetSearch(is,value,NULL);
+    return valenc <= intrev32ifbe(is->encoding) && intsetSearch(is,value,NULL);
 }
 
 /* Return random member */
 int64_t intsetRandom(intset *is) {
-    return _intsetGet(is,rand()%is->length);
+    return _intsetGet(is,rand()%intrev32ifbe(is->length));
 }
 
 /* Sets the value to the value at the given position. When this position is
  * out of range the function returns 0, when in range it returns 1. */
 uint8_t intsetGet(intset *is, uint32_t pos, int64_t *value) {
-    if (pos < is->length) {
+    if (pos < intrev32ifbe(is->length)) {
         *value = _intsetGet(is,pos);
         return 1;
     }
@@ -237,20 +243,20 @@ uint8_t intsetGet(intset *is, uint32_t pos, int64_t *value) {
 
 /* Return intset length */
 uint32_t intsetLen(intset *is) {
-    return is->length;
+    return intrev32ifbe(is->length);
 }
 
 /* Return intset blob size in bytes. */
 size_t intsetBlobLen(intset *is) {
-    return sizeof(intset)+is->length*is->encoding;
+    return sizeof(intset)+intrev32ifbe(is->length)*intrev32ifbe(is->encoding);
 }
 
 #ifdef INTSET_TEST_MAIN
 #include <sys/time.h>
 
 void intsetRepr(intset *is) {
     int i;
-    for (i = 0; i < is->length; i++) {
+    for (i = 0; i < intrev32ifbe(is->length); i++) {
         printf("%lld\n", (uint64_t)_intsetGet(is,i));
     }
     printf("\n");
@@ -296,11 +302,13 @@ intset *createSet(int bits, int size) {
 void checkConsistency(intset *is) {
     int i;
 
-    for (i = 0; i < (is->length-1); i++) {
-        if (is->encoding == INTSET_ENC_INT16) {
+    for (i = 0; i < (intrev32ifbe(is->length)-1); i++) {
+        uint32_t encoding = intrev32ifbe(is->encoding);
+
+        if (encoding == INTSET_ENC_INT16) {
             int16_t *i16 = (int16_t*)is->contents;
             assert(i16[i] < i16[i+1]);
-        } else if (is->encoding == INTSET_ENC_INT32) {
+        } else if (encoding == INTSET_ENC_INT32) {
             int32_t *i32 = (int32_t*)is->contents;
             assert(i32[i] < i32[i+1]);
         } else {
@@ -346,26 +354,26 @@ int main(int argc, char **argv) {
             is = intsetAdd(is,rand()%0x800,&success);
             if (success) inserts++;
         }
-        assert(is->length == inserts);
+        assert(intrev32ifbe(is->length) == inserts);
         checkConsistency(is);
         ok();
     }
 
     printf("Upgrade from int16 to int32: "); {
         is = intsetNew();
         is = intsetAdd(is,32,NULL);
-        assert(is->encoding == INTSET_ENC_INT16);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT16);
         is = intsetAdd(is,65535,NULL);
-        assert(is->encoding == INTSET_ENC_INT32);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT32);
         assert(intsetFind(is,32));
         assert(intsetFind(is,65535));
         checkConsistency(is);
 
         is = intsetNew();
         is = intsetAdd(is,32,NULL);
-        assert(is->encoding == INTSET_ENC_INT16);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT16);
         is = intsetAdd(is,-65535,NULL);
-        assert(is->encoding == INTSET_ENC_INT32);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT32);
         assert(intsetFind(is,32));
         assert(intsetFind(is,-65535));
         checkConsistency(is);
@@ -375,18 +383,18 @@ int main(int argc, char **argv) {
     printf("Upgrade from int16 to int64: "); {
         is = intsetNew();
         is = intsetAdd(is,32,NULL);
-        assert(is->encoding == INTSET_ENC_INT16);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT16);
         is = intsetAdd(is,4294967295,NULL);
-        assert(is->encoding == INTSET_ENC_INT64);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT64);
         assert(intsetFind(is,32));
         assert(intsetFind(is,4294967295));
         checkConsistency(is);
 
         is = intsetNew();
         is = intsetAdd(is,32,NULL);
-        assert(is->encoding == INTSET_ENC_INT16);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT16);
         is = intsetAdd(is,-4294967295,NULL);
-        assert(is->encoding == INTSET_ENC_INT64);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT64);
         assert(intsetFind(is,32));
         assert(intsetFind(is,-4294967295));
         checkConsistency(is);
@@ -396,18 +404,18 @@ int main(int argc, char **argv) {
     printf("Upgrade from int32 to int64: "); {
         is = intsetNew();
         is = intsetAdd(is,65535,NULL);
-        assert(is->encoding == INTSET_ENC_INT32);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT32);
         is = intsetAdd(is,4294967295,NULL);
-        assert(is->encoding == INTSET_ENC_INT64);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT64);
         assert(intsetFind(is,65535));
         assert(intsetFind(is,4294967295));
         checkConsistency(is);
 
         is = intsetNew();
         is = intsetAdd(is,65535,NULL);
-        assert(is->encoding == INTSET_ENC_INT32);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT32);
         is = intsetAdd(is,-4294967295,NULL);
-        assert(is->encoding == INTSET_ENC_INT64);
+        assert(intrev32ifbe(is->encoding) == INTSET_ENC_INT64);
         assert(intsetFind(is,65535));
         assert(intsetFind(is,-4294967295));
         checkConsistency(is);