@@ -1123,10 +1123,15 @@ dictType BenchmarkDictType = {
     NULL
 };
 
+#define start_benchmark() start = timeInMilliseconds()
+#define end_benchmark(msg) do { \
+    elapsed = timeInMilliseconds()-start; \
+    printf(msg ": %ld items in %lld ms\n", count, elapsed); \
+} while(0);
+
 /* dict-benchmark [count] */
 int main(int argc, char **argv) {
     long j;
-    long hits = 0, misses = 0;
     long long start, elapsed;
     dict *dict = dictCreate(&BenchmarkDictType,NULL);
     long count = 0;
@@ -1137,13 +1142,31 @@ int main(int argc, char **argv) {
         count = 5000000;
     }
 
-    start = timeInMilliseconds();
+    start_benchmark();
     for (j = 0; j < count; j++) {
         int retval = dictAdd(dict,sdsfromlonglong(j),(void*)j);
         assert(retval == DICT_OK);
     }
-    elapsed = timeInMilliseconds()-start;
-    printf("Inserting 5M items: %lld ms\n", elapsed);
+    end_benchmark("Inserting");
     assert((long)dictSize(dict) == count);
+
+    start_benchmark();
+    for (j = 0; j < count; j++) {
+        sds key = sdsfromlonglong(rand() % count);
+        dictEntry *de = dictFind(dict,key);
+        assert(de != NULL);
+        sdsfree(key);
+    }
+    end_benchmark("Accessing existing");
+
+    start_benchmark();
+    for (j = 0; j < count; j++) {
+        sds key = sdsfromlonglong(rand() % count);
+        key[0] = 'X';
+        dictEntry *de = dictFind(dict,key);
+        assert(de == NULL);
+        sdsfree(key);
+    }
+    end_benchmark("Accessing missing");
 }
 #endif