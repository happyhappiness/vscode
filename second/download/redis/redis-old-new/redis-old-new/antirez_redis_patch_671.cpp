@@ -261,6 +261,100 @@ int64_t intsetRandom(intset *is) {
     return _intsetGet(is,rand()%intrev32ifbe(is->length));
 }
 
+/* How many times bigger should the set length be compared to the requested 
+ * count of members for us to use the Floyd algorithm instead of
+   the Knuth algorithm */
+#define RANDOMMEMBERS_ALGORITHM_SELECTION_RATIO (2)
+
+/* Copies 'count' random members from the set into the 'values' array. 
+   'values' must be an array of int64_t values, of length 'count'.
+   Returns the amount of items returned. If this amount is less than 'count',
+   then the remaining 'values' are left uninitialized. */
+int intsetRandomMembers(intset *is, int64_t* values, int count) {
+
+    /* We don't check that is and values are non-NULL - the caller must
+       play nice. */
+    /* redisAssert(is != NULL);
+       redisAssert(values != NULL);
+       redisAssert(count > 0); */
+
+    int length = intsetLen(is);
+
+    if (count > length) {
+        /* Return everything in the set */
+        count = length;
+    }
+
+    /* Choose between the Knuth shuffle algorithm, O(1) space, O(length) time,
+       and the Floyd algorithm, O(length) space, O(count) time. */
+    if ((RANDOMMEMBERS_ALGORITHM_SELECTION_RATIO * count) > length) {
+
+        /* If the count of members requested is almost the length of the set,
+           use the Knuth shuffle algorithm, O(1) space, O(length) time. */
+
+        /* First, fill the values array with unique random indexes inside
+           the set. */
+        int in, im, rn, rm;
+        im = 0;
+        for (in = 0; 
+             in < length && im < count; 
+             in++) {
+
+            rn = length - in;
+            rm = count - im;
+            if (rand() % rn < rm) {
+                values[im++] = in;
+            }
+        }
+
+    } else {
+
+        /* If the length is considerably more than the count of members 
+           requested, use Robert Floyd's algorithm, O(length) space, 
+           O(count) time.
+           Based on Jon Bentley's Programming Pearls */
+
+        int64_t *is_used = zcalloc(sizeof(int64_t) * length);
+        int in, im, r;
+
+        r = 0;
+        im = 0;
+
+        for (in = length - count; 
+             in < length && im < count; 
+             in++) {
+
+            /* Generate a random number r */
+            r = rand() % (in + 1); 
+
+            /* Do we already have the value in r? */
+            if (is_used[r]) {
+            
+                /* Use in instead of the generated number */
+                r = in; 
+            }
+
+            values[im++] = r ;
+
+            /* Mark it as used */
+            is_used[r] = 1;
+        }
+
+        zfree(is_used);
+    }
+
+    /* Replace each random index with the value stored there in the intset */
+    uint8_t encoding = intrev32ifbe(is->encoding);
+    for (int currentValue = 0;
+         currentValue < count;
+         currentValue++) {
+        values[currentValue] = 
+            _intsetGetEncoded(is, values[currentValue], encoding);
+    }
+
+    return count;
+}
+
 /* Sets the value to the value at the given position. When this position is
  * out of range the function returns 0, when in range it returns 1. */
 uint8_t intsetGet(intset *is, uint32_t pos, int64_t *value) {
@@ -363,8 +457,10 @@ int main(int argc, char **argv) {
         assert(_intsetValueEncoding(+2147483647) == INTSET_ENC_INT32);
         assert(_intsetValueEncoding(-2147483649) == INTSET_ENC_INT64);
         assert(_intsetValueEncoding(+2147483648) == INTSET_ENC_INT64);
-        assert(_intsetValueEncoding(-9223372036854775808ull) == INTSET_ENC_INT64);
-        assert(_intsetValueEncoding(+9223372036854775807ull) == INTSET_ENC_INT64);
+        assert(_intsetValueEncoding(-9223372036854775808ull) == 
+                    INTSET_ENC_INT64);
+        assert(_intsetValueEncoding(+9223372036854775807ull) ==
+                    INTSET_ENC_INT64);
         ok();
     }
 
@@ -461,7 +557,8 @@ int main(int argc, char **argv) {
 
         start = usec();
         for (i = 0; i < num; i++) intsetSearch(is,rand() % ((1<<bits)-1),NULL);
-        printf("%ld lookups, %ld element set, %lldusec\n",num,size,usec()-start);
+        printf("%ld lookups, %ld element set, %lldusec\n",
+               num,size,usec()-start);
     }
 
     printf("Stress add+delete: "); {