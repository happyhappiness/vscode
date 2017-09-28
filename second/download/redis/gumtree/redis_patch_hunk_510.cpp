             int64_t *i64 = (int64_t*)is->contents;
             assert(i64[i] < i64[i+1]);
         }
     }
 }
 
-int main(int argc, char **argv) {
+#define UNUSED(x) (void)(x)
+int intsetTest(int argc, char **argv) {
     uint8_t success;
     int i;
     intset *is;
-    sranddev();
+    srand(time(NULL));
+
+    UNUSED(argc);
+    UNUSED(argv);
 
     printf("Value encodings: "); {
         assert(_intsetValueEncoding(-32768) == INTSET_ENC_INT16);
         assert(_intsetValueEncoding(+32767) == INTSET_ENC_INT16);
         assert(_intsetValueEncoding(-32769) == INTSET_ENC_INT32);
         assert(_intsetValueEncoding(+32768) == INTSET_ENC_INT32);
         assert(_intsetValueEncoding(-2147483648) == INTSET_ENC_INT32);
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
 
     printf("Basic adding: "); {
         is = intsetNew();
         is = intsetAdd(is,5,&success); assert(success);
