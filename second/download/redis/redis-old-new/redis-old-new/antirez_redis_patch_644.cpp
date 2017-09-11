@@ -40,7 +40,7 @@
 #endif
 
 /* Optimization levels for size-based filling */
-static const size_t optimization_level[] = { 4096, 8192, 16384, 32768, 65536 };
+static const size_t optimization_level[] = {4096, 8192, 16384, 32768, 65536};
 
 /* Maximum size in bytes of any multi-element ziplist.
  * Larger values will live in their own isolated ziplists. */
@@ -527,7 +527,7 @@ quicklist *quicklistAppendValuesFromZiplist(quicklist *quicklist,
     unsigned char *value;
     unsigned int sz;
     long long longval;
-    char longstr[32] = { 0 };
+    char longstr[32] = {0};
 
     unsigned char *p = ziplistIndex(zl, 0);
     while (ziplistGet(p, &value, &sz, &longval)) {
@@ -1267,7 +1267,7 @@ void quicklistRotate(quicklist *quicklist) {
     unsigned char *value;
     long long longval;
     unsigned int sz;
-    char longstr[32] = { 0 };
+    char longstr[32] = {0};
     ziplistGet(p, &value, &sz, &longval);
 
     /* If value found is NULL, then ziplistGet populated longval instead */
@@ -1582,7 +1582,7 @@ static int _ql_verify(quicklist *ql, uint32_t len, uint32_t count,
 
 /* Generate new string concatenating integer i against string 'prefix' */
 static char *genstr(char *prefix, int i) {
-    static char result[64] = { 0 };
+    static char result[64] = {0};
     snprintf(result, sizeof(result), "%s%d", prefix, i);
     return result;
 }
@@ -1598,7 +1598,7 @@ int quicklistTest(int argc, char *argv[]) {
 
     printf("Starting optimization offset at: %d\n", optimize_start);
 
-    int options[] = { 0, 1, 2, 3, 4, 5, 6, 10 };
+    int options[] = {0, 1, 2, 3, 4, 5, 6, 10};
     size_t option_count = sizeof(options) / sizeof(*options);
     long long runtime[option_count];
 
@@ -2247,12 +2247,12 @@ int quicklistTest(int argc, char *argv[]) {
         for (int f = optimize_start; f < 16; f++) {
             TEST_DESC("lrem test at fill %d at compress %d", f, options[_i]) {
                 quicklist *ql = quicklistNew(f, options[_i]);
-                char *words[] = { "abc", "foo", "bar",  "foobar", "foobared",
-                                  "zap", "bar", "test", "foo" };
-                char *result[] = { "abc", "foo",  "foobar", "foobared",
-                                   "zap", "test", "foo" };
-                char *resultB[] = { "abc",      "foo", "foobar",
-                                    "foobared", "zap", "test" };
+                char *words[] = {"abc", "foo", "bar",  "foobar", "foobared",
+                                 "zap", "bar", "test", "foo"};
+                char *result[] = {"abc", "foo",  "foobar", "foobared",
+                                  "zap", "test", "foo"};
+                char *resultB[] = {"abc",      "foo", "foobar",
+                                   "foobared", "zap", "test"};
                 for (int i = 0; i < 9; i++)
                     quicklistPushTail(ql, words[i], strlen(words[i]));
 
@@ -2355,7 +2355,7 @@ int quicklistTest(int argc, char *argv[]) {
                 /* Check results after deletion of "hij" */
                 iter = quicklistGetIterator(ql, AL_START_HEAD);
                 i = 0;
-                char *vals[] = { "abc", "def", "jkl", "oop" };
+                char *vals[] = {"abc", "def", "jkl", "oop"};
                 while (quicklistNext(iter, &entry)) {
                     if (!quicklistCompare(entry.zi, (unsigned char *)vals[i],
                                           3)) {
@@ -2554,7 +2554,7 @@ int quicklistTest(int argc, char *argv[]) {
     }
 
     /* Run a longer test of compression depth outside of primary test loop. */
-    int list_sizes[] = { 250, 251, 500, 999, 1000 };
+    int list_sizes[] = {250, 251, 500, 999, 1000};
     long long start = mstime();
     for (int list = 0; list < (int)(sizeof(list_sizes) / sizeof(*list_sizes));
          list++) {