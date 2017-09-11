@@ -45,7 +45,11 @@
 
 #include "dict.h"
 #include "zmalloc.h"
+#ifndef DICT_BENCHMARK_MAIN
 #include "redisassert.h"
+#else
+#include <assert.h>
+#endif
 
 /* Using dictEnableResize() / dictDisableResize() we make possible to
  * enable/disable resizing of the hash table as needed. This is very important
@@ -1083,3 +1087,55 @@ void dictGetStats(char *buf, size_t bufsize, dict *d) {
     /* Make sure there is a NULL term at the end. */
     if (orig_bufsize) orig_buf[orig_bufsize-1] = '\0';
 }
+
+/* ------------------------------- Benchmark ---------------------------------*/
+
+#ifdef DICT_BENCHMARK_MAIN
+
+#include "sds.h"
+
+unsigned int hashCallback(const void *key) {
+    return dictGenHashFunction((unsigned char*)key, sdslen((char*)key));
+}
+
+int compareCallback(void *privdata, const void *key1, const void *key2) {
+    int l1,l2;
+    DICT_NOTUSED(privdata);
+
+    l1 = sdslen((sds)key1);
+    l2 = sdslen((sds)key2);
+    if (l1 != l2) return 0;
+    return memcmp(key1, key2, l1) == 0;
+}
+
+void freeCallback(void *privdata, void *val) {
+    DICT_NOTUSED(privdata);
+
+    sdsfree(val);
+}
+
+dictType BenchmarkDictType = {
+    hashCallback,
+    NULL,
+    NULL,
+    compareCallback,
+    freeCallback,
+    NULL
+};
+
+int main(void) {
+    long j;
+    long hits = 0, misses = 0;
+    long long start, elapsed;
+    dict *dict = dictCreate(&BenchmarkDictType,NULL);
+
+    start = timeInMilliseconds();
+    for (j = 0; j < 5000000; j++) {
+        int retval = dictAdd(dict,sdsfromlonglong(j),(void*)j);
+        assert(retval == DICT_OK);
+    }
+    elapsed = timeInMilliseconds()-start;
+    printf("Inserting 5M items: %lld ms\n", elapsed);
+    assert(dictSize(dict) == 5000000);
+}
+#endif