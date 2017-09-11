@@ -38,6 +38,11 @@
 #include <stdio.h> /* for printf (debug printing), snprintf (genstr) */
 #endif
 
+/* Optimization levels for size-based filling */
+static const size_t optimization_level[] = { 4096, 8192, 16384, 32768, 65536 };
+
+#define SIZE_SAFETY_LIMIT 8192
+
 /* If not verbose testing, remove all debug printing. */
 #ifndef REDIS_TEST_VERBOSE
 #define D(...)
@@ -82,6 +87,7 @@ static quicklistNode *quicklistCreateNode(void) {
         return NULL;
     node->zl = NULL;
     node->count = 0;
+    node->sz = 0;
     node->next = node->prev = NULL;
     return node;
 }
@@ -156,12 +162,86 @@ static void _quicklistInsertNodeAfter(quicklist *quicklist,
     __quicklistInsertNode(quicklist, old_node, new_node, 1);
 }
 
+static int _quicklistNodeSizeMeetsOptimizationRequirement(const size_t sz,
+                                                          const int fill) {
+    if (fill >= 0)
+        return 0;
+
+    size_t offset = (-fill) - 1;
+    if (offset < (sizeof(optimization_level) / sizeof(*optimization_level))) {
+        if (sz <= optimization_level[offset]) {
+            return 1;
+        } else {
+            return 0;
+        }
+    } else {
+        return 0;
+    }
+}
+
+#define sizeMeetsSafetyLimit(sz) ((sz) <= SIZE_SAFETY_LIMIT)
+
+static int _quicklistNodeAllowInsert(const quicklistNode *node, const int fill,
+                                     const size_t sz) {
+    if (!node)
+        return 0;
+
+    int ziplist_overhead;
+    /* size of previous offset */
+    if (sz < 254)
+        ziplist_overhead = 1;
+    else
+        ziplist_overhead = 5;
+
+    /* size of forward offset */
+    if (sz < 64)
+        ziplist_overhead += 1;
+    else if (sz < 16384)
+        ziplist_overhead += 2;
+    else
+        ziplist_overhead += 5;
+
+    /* new_sz overestimates if 'sz' encodes to an integer type */
+    unsigned int new_sz = node->sz + sz + ziplist_overhead;
+    if (_quicklistNodeSizeMeetsOptimizationRequirement(new_sz, fill))
+        return 1;
+    else if (!sizeMeetsSafetyLimit(new_sz))
+        return 0;
+    else if ((int)node->count < fill)
+        return 1;
+    else
+        return 0;
+}
+
+static int _quicklistNodeAllowMerge(const quicklistNode *a,
+                                    const quicklistNode *b, const int fill) {
+    if (!a || !b)
+        return 0;
+
+    /* approximate merged ziplist size (- 11 to remove one ziplist
+     * header/trailer) */
+    unsigned int merge_sz = a->sz + b->sz - 11;
+    if (_quicklistNodeSizeMeetsOptimizationRequirement(merge_sz, fill))
+        return 1;
+    else if (!sizeMeetsSafetyLimit(merge_sz))
+        return 0;
+    else if ((int)(a->count + b->count) <= fill)
+        return 1;
+    else
+        return 0;
+}
+
+#define quicklistNodeUpdateSz(node)                                            \
+    do {                                                                       \
+        (node)->sz = ziplistBlobLen((node)->zl);                               \
+    } while (0)
+
 /* Add new entry to head of quicklist.
  *
  * Returns 'quicklist' argument. */
-quicklist *quicklistPushHead(quicklist *quicklist, const size_t fill,
-                             void *value, size_t sz) {
-    if (quicklist->head && quicklist->head->count < fill) {
+quicklist *quicklistPushHead(quicklist *quicklist, const int fill, void *value,
+                             size_t sz) {
+    if (_quicklistNodeAllowInsert(quicklist->head, fill, sz)) {
         quicklist->head->zl =
             ziplistPush(quicklist->head->zl, value, sz, ZIPLIST_HEAD);
     } else {
@@ -172,15 +252,16 @@ quicklist *quicklistPushHead(quicklist *quicklist, const size_t fill,
     }
     quicklist->count++;
     quicklist->head->count++;
+    quicklistNodeUpdateSz(quicklist->head);
     return quicklist;
 }
 
 /* Add new node to tail of quicklist.
  *
  * Returns 'quicklist' argument. */
-quicklist *quicklistPushTail(quicklist *quicklist, const size_t fill,
-                             void *value, size_t sz) {
-    if (quicklist->tail && quicklist->tail->count < fill) {
+quicklist *quicklistPushTail(quicklist *quicklist, const int fill, void *value,
+                             size_t sz) {
+    if (_quicklistNodeAllowInsert(quicklist->tail, fill, sz)) {
         quicklist->tail->zl =
             ziplistPush(quicklist->tail->zl, value, sz, ZIPLIST_TAIL);
     } else {
@@ -191,6 +272,7 @@ quicklist *quicklistPushTail(quicklist *quicklist, const size_t fill,
     }
     quicklist->count++;
     quicklist->tail->count++;
+    quicklistNodeUpdateSz(quicklist->tail);
     return quicklist;
 }
 
@@ -202,6 +284,7 @@ void quicklistAppendZiplist(quicklist *quicklist, unsigned char *zl) {
 
     node->zl = zl;
     node->count = ziplistLen(node->zl);
+    node->sz = ziplistBlobLen(zl);
 
     _quicklistInsertNodeAfter(quicklist, quicklist->tail, node);
     quicklist->count += node->count;
@@ -214,8 +297,7 @@ void quicklistAppendZiplist(quicklist *quicklist, unsigned char *zl) {
  *
  * Returns 'quicklist' argument. Frees passed-in ziplist 'zl' */
 quicklist *quicklistAppendValuesFromZiplist(quicklist *quicklist,
-                                            const size_t fill,
-                                            unsigned char *zl) {
+                                            const int fill, unsigned char *zl) {
     unsigned char *value;
     unsigned int sz;
     long long longval;
@@ -238,7 +320,7 @@ quicklist *quicklistAppendValuesFromZiplist(quicklist *quicklist,
 /* Create new (potentially multi-node) quicklist from a single existing ziplist.
  *
  * Returns new quicklist.  Frees passed-in ziplist 'zl'. */
-quicklist *quicklistCreateFromZiplist(size_t fill, unsigned char *zl) {
+quicklist *quicklistCreateFromZiplist(int fill, unsigned char *zl) {
     return quicklistAppendValuesFromZiplist(quicklistCreate(), fill, zl);
 }
 
@@ -278,8 +360,11 @@ static int quicklistDelIndex(quicklist *quicklist, quicklistNode *node,
     int gone = 0;
     node->zl = ziplistDelete(node->zl, p);
     node->count--;
-    if (node->count == 0)
+    if (node->count == 0) {
         gone = 1;
+    } else {
+        quicklistNodeUpdateSz(node);
+    }
     quicklist->count--;
     quicklistDeleteIfEmpty(quicklist, node);
     /* If we deleted all the nodes, our returned pointer is no longer valid */
@@ -364,6 +449,7 @@ static quicklistNode *_quicklistZiplistMerge(quicklist *quicklist,
             keep = a;
         }
         keep->count = ziplistLen(keep->zl);
+        quicklistNodeUpdateSz(keep);
 
         nokeep->count = 0;
         __quicklistDelNode(quicklist, nokeep);
@@ -383,7 +469,7 @@ static quicklistNode *_quicklistZiplistMerge(quicklist *quicklist,
  *   - (center->prev, center)
  *   - (center, center->next)
  */
-static void _quicklistMergeNodes(quicklist *quicklist, const size_t fill,
+static void _quicklistMergeNodes(quicklist *quicklist, const int fill,
                                  quicklistNode *center) {
     quicklistNode *prev, *prev_prev, *next, *next_next, *target;
     prev = prev_prev = next = next_next = target = NULL;
@@ -401,19 +487,19 @@ static void _quicklistMergeNodes(quicklist *quicklist, const size_t fill,
     }
 
     /* Try to merge prev_prev and prev */
-    if (prev && prev_prev && (prev->count + prev_prev->count) <= fill) {
+    if (_quicklistNodeAllowMerge(prev, prev_prev, fill)) {
         _quicklistZiplistMerge(quicklist, prev_prev, prev);
         prev_prev = prev = NULL; /* they could have moved, invalidate them. */
     }
 
     /* Try to merge next and next_next */
-    if (next && next_next && (next->count + next_next->count) <= fill) {
+    if (_quicklistNodeAllowMerge(next, next_next, fill)) {
         _quicklistZiplistMerge(quicklist, next, next_next);
         next = next_next = NULL; /* they could have moved, invalidate them. */
     }
 
     /* Try to merge center node and previous node */
-    if (center->prev && (center->count + center->prev->count) <= fill) {
+    if (_quicklistNodeAllowMerge(center, center->prev, fill)) {
         target = _quicklistZiplistMerge(quicklist, center->prev, center);
         center = NULL; /* center could have been deleted, invalidate it. */
     } else {
@@ -422,8 +508,7 @@ static void _quicklistMergeNodes(quicklist *quicklist, const size_t fill,
     }
 
     /* Use result of center merge (or original) to merge with next node. */
-    if (target && target->next &&
-        (target->count + target->next->count) <= fill) {
+    if (_quicklistNodeAllowMerge(target, target->next, fill)) {
         _quicklistZiplistMerge(quicklist, target, target->next);
     }
 }
@@ -475,9 +560,11 @@ static quicklistNode *_quicklistSplitNode(quicklistNode *node, int offset,
 
     node->zl = ziplistDeleteRange(node->zl, orig_start, orig_extent);
     node->count = ziplistLen(node->zl);
+    quicklistNodeUpdateSz(node);
 
     new_node->zl = ziplistDeleteRange(new_node->zl, new_start, new_extent);
     new_node->count = ziplistLen(new_node->zl);
+    quicklistNodeUpdateSz(new_node);
 
     D("After split lengths: orig (%d), new (%d)", node->count, new_node->count);
     return new_node;
@@ -487,7 +574,7 @@ static quicklistNode *_quicklistSplitNode(quicklistNode *node, int offset,
  *
  * If after==1, the new value is inserted after 'entry', otherwise
  * the new value is inserted before 'entry'. */
-static void _quicklistInsert(quicklist *quicklist, const size_t fill,
+static void _quicklistInsert(quicklist *quicklist, const int fill,
                              quicklistEntry *entry, void *value,
                              const size_t sz, int after) {
     int full = 0, at_tail = 0, at_head = 0, full_next = 0, full_prev = 0;
@@ -506,7 +593,7 @@ static void _quicklistInsert(quicklist *quicklist, const size_t fill,
     }
 
     /* Populate accounting flags for easier boolean checks later */
-    if (node->count >= fill) {
+    if (!_quicklistNodeAllowInsert(node, fill, sz)) {
         D("Current node is full with count %d with requested fill %lu",
           node->count, fill);
         full = 1;
@@ -515,7 +602,7 @@ static void _quicklistInsert(quicklist *quicklist, const size_t fill,
     if (after && (ziplistNext(node->zl, entry->zi) == NULL)) {
         D("At Tail of current ziplist");
         at_tail = 1;
-        if (node->next && node->next->count >= fill) {
+        if (!_quicklistNodeAllowInsert(node->next, fill, sz)) {
             D("Next node is full too.");
             full_next = 1;
         }
@@ -524,7 +611,7 @@ static void _quicklistInsert(quicklist *quicklist, const size_t fill,
     if (!after && (ziplistPrev(node->zl, entry->zi) == NULL)) {
         D("At Head");
         at_head = 1;
-        if (node->prev && node->prev->count >= fill) {
+        if (!_quicklistNodeAllowInsert(node->prev, fill, sz)) {
             D("Prev node is full too.");
             full_prev = 1;
         }
@@ -540,24 +627,28 @@ static void _quicklistInsert(quicklist *quicklist, const size_t fill,
             node->zl = ziplistInsert(node->zl, next, value, sz);
         }
         node->count++;
+        quicklistNodeUpdateSz(node);
     } else if (!full && !after) {
         D("Not full, inserting before current position.");
         node->zl = ziplistInsert(node->zl, entry->zi, value, sz);
         node->count++;
+        quicklistNodeUpdateSz(node);
     } else if (full && at_tail && node->next && !full_next && after) {
         /* If we are: at tail, next has free space, and inserting after:
          *   - insert entry at head of next node. */
         D("Full and tail, but next isn't full; inserting next node head");
         new_node = node->next;
         new_node->zl = ziplistPush(new_node->zl, value, sz, ZIPLIST_HEAD);
         new_node->count++;
+        quicklistNodeUpdateSz(new_node);
     } else if (full && at_head && node->prev && !full_prev && !after) {
         /* If we are: at head, previous has free space, and inserting before:
          *   - insert entry at tail of previous node. */
         D("Full and head, but prev isn't full, inserting prev node tail");
         new_node = node->prev;
         new_node->zl = ziplistPush(new_node->zl, value, sz, ZIPLIST_TAIL);
         new_node->count++;
+        quicklistNodeUpdateSz(new_node);
     } else if (full && ((at_tail && node->next && full_next && after) ||
                         (at_head && node->prev && full_prev && !after))) {
         /* If we are: full, and our prev/next is full, then:
@@ -566,6 +657,7 @@ static void _quicklistInsert(quicklist *quicklist, const size_t fill,
         new_node = quicklistCreateNode();
         new_node->zl = ziplistPush(ziplistNew(), value, sz, ZIPLIST_HEAD);
         new_node->count++;
+        quicklistNodeUpdateSz(new_node);
         __quicklistInsertNode(quicklist, node, new_node, after);
     } else if (full) {
         /* else, node is full we need to split it. */
@@ -575,20 +667,21 @@ static void _quicklistInsert(quicklist *quicklist, const size_t fill,
         new_node->zl = ziplistPush(new_node->zl, value, sz,
                                    after ? ZIPLIST_HEAD : ZIPLIST_TAIL);
         new_node->count++;
+        quicklistNodeUpdateSz(new_node);
         __quicklistInsertNode(quicklist, node, new_node, after);
         _quicklistMergeNodes(quicklist, fill, node);
     }
 
     quicklist->count++;
 }
 
-void quicklistInsertBefore(quicklist *quicklist, const size_t fill,
+void quicklistInsertBefore(quicklist *quicklist, const int fill,
                            quicklistEntry *entry, void *value,
                            const size_t sz) {
     _quicklistInsert(quicklist, fill, entry, value, sz, 0);
 }
 
-void quicklistInsertAfter(quicklist *quicklist, const size_t fill,
+void quicklistInsertAfter(quicklist *quicklist, const int fill,
                           quicklistEntry *entry, void *value, const size_t sz) {
     _quicklistInsert(quicklist, fill, entry, value, sz, 1);
 }
@@ -665,6 +758,7 @@ int quicklistDelRange(quicklist *quicklist, const long start,
         } else {
             node->zl = ziplistDeleteRange(node->zl, entry.offset, del);
             node->count -= del;
+            quicklistNodeUpdateSz(node);
             quicklist->count -= del;
             quicklistDeleteIfEmpty(quicklist, node);
         }
@@ -836,6 +930,7 @@ quicklist *quicklistDup(quicklist *orig) {
 
         node->count = current->count;
         copy->count += node->count;
+        node->sz = current->sz;
 
         _quicklistInsertNodeAfter(copy, copy->tail, node);
     }
@@ -912,7 +1007,7 @@ int quicklistIndex(const quicklist *quicklist, const long long idx,
 }
 
 /* Rotate quicklist by moving the tail element to the head. */
-void quicklistRotate(quicklist *quicklist, const size_t fill) {
+void quicklistRotate(quicklist *quicklist, const int fill) {
     if (quicklist->count <= 1)
         return;
 
@@ -1035,7 +1130,7 @@ int quicklistPop(quicklist *quicklist, int where, unsigned char **data,
 }
 
 /* Wrapper to allow argument-based switching between HEAD/TAIL pop */
-void quicklistPush(quicklist *quicklist, const size_t fill, void *value,
+void quicklistPush(quicklist *quicklist, const int fill, void *value,
                    const size_t sz, int where) {
     if (where == QUICKLIST_HEAD) {
         quicklistPushHead(quicklist, fill, value, sz);
@@ -1202,6 +1297,10 @@ static char *genstr(char *prefix, int i) {
 /* main test, but callable from other files */
 int quicklistTest(int argc, char *argv[]) {
     unsigned int err = 0;
+    int optimize_start =
+        -(int)(sizeof(optimization_level) / sizeof(*optimization_level));
+
+    printf("Starting optimization offset at: %d\n", optimize_start);
 
     UNUSED(argc);
     UNUSED(argv);
@@ -1228,8 +1327,8 @@ int quicklistTest(int argc, char *argv[]) {
         quicklistRelease(ql);
     }
 
-    for (size_t f = 0; f < 32; f++) {
-        TEST_DESC("add to tail 5x at fill %lu", f) {
+    for (int f = optimize_start; f < 32; f++) {
+        TEST_DESC("add to tail 5x at fill %d", f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 5; i++)
                 quicklistPushTail(ql, f, genstr("hello", i), 32);
@@ -1241,8 +1340,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 32; f++) {
-        TEST_DESC("add to head 5x at fill %lu", f) {
+    for (int f = optimize_start; f < 32; f++) {
+        TEST_DESC("add to head 5x at fill %d", f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 5; i++)
                 quicklistPushHead(ql, f, genstr("hello", i), 32);
@@ -1254,8 +1353,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 512; f++) {
-        TEST_DESC("add to tail 500x at fill %lu", f) {
+    for (int f = optimize_start; f < 512; f++) {
+        TEST_DESC("add to tail 500x at fill %d", f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 500; i++)
                 quicklistPushTail(ql, f, genstr("hello", i), 32);
@@ -1267,8 +1366,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 512; f++) {
-        TEST_DESC("add to head 500x at fill %lu", f) {
+    for (int f = optimize_start; f < 512; f++) {
+        TEST_DESC("add to head 500x at fill %d", f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 500; i++)
                 quicklistPushHead(ql, f, genstr("hello", i), 32);
@@ -1287,7 +1386,7 @@ int quicklistTest(int argc, char *argv[]) {
         quicklistRelease(ql);
     }
 
-    for (size_t f = 0; f < 32; f++) {
+    for (int f = optimize_start; f < 32; f++) {
         TEST("rotate one val once") {
             quicklist *ql = quicklistCreate();
             quicklistPushHead(ql, F, "hello", 6);
@@ -1297,8 +1396,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 1024; f++) {
-        TEST_DESC("rotate 500 val 5000 times at fill %lu", f) {
+    for (int f = optimize_start; f < 1024; f++) {
+        TEST_DESC("rotate 500 val 5000 times at fill %d", f) {
             quicklist *ql = quicklistCreate();
             quicklistPushHead(ql, f, "900", 3);
             quicklistPushHead(ql, f, "7000", 4);
@@ -1479,8 +1578,8 @@ int quicklistTest(int argc, char *argv[]) {
         quicklistRelease(ql);
     }
 
-    for (size_t f = 0; f < 12; f++) {
-        TEST_DESC("insert once in elements while iterating at fill %lu\n", f) {
+    for (int f = optimize_start; f < 12; f++) {
+        TEST_DESC("insert once in elements while iterating at fill %d\n", f) {
             quicklist *ql = quicklistCreate();
             quicklistPushTail(ql, f, "abc", 3);
             quicklistPushTail(ql, 1, "def", 3); /* force to unique node */
@@ -1534,9 +1633,9 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 1024; f++) {
+    for (int f = optimize_start; f < 1024; f++) {
         TEST_DESC("insert [before] 250 new in middle of 500 elements at fill"
-                  " %ld",
+                  " %d",
                   f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 500; i++)
@@ -1552,9 +1651,9 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 1024; f++) {
-        TEST_DESC(
-            "insert [after] 250 new in middle of 500 elements at fill %ld", f) {
+    for (int f = optimize_start; f < 1024; f++) {
+        TEST_DESC("insert [after] 250 new in middle of 500 elements at fill %d",
+                  f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 500; i++)
                 quicklistPushHead(ql, f, genstr("hello", i), 32);
@@ -1604,8 +1703,8 @@ int quicklistTest(int argc, char *argv[]) {
         quicklistRelease(copy);
     }
 
-    for (size_t f = 0; f < 512; f++) {
-        TEST_DESC("index 1,200 from 500 list at fill %lu", f) {
+    for (int f = optimize_start; f < 512; f++) {
+        TEST_DESC("index 1,200 from 500 list at fill %d", f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 500; i++)
                 quicklistPushTail(ql, f, genstr("hello", i + 1), 32);
@@ -1623,7 +1722,7 @@ int quicklistTest(int argc, char *argv[]) {
             quicklistRelease(ql);
         }
 
-        TEST_DESC("index -1,-2 from 500 list at fill %lu", f) {
+        TEST_DESC("index -1,-2 from 500 list at fill %d", f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 500; i++)
                 quicklistPushTail(ql, f, genstr("hello", i + 1), 32);
@@ -1641,7 +1740,7 @@ int quicklistTest(int argc, char *argv[]) {
             quicklistRelease(ql);
         }
 
-        TEST_DESC("index -100 from 500 list at fill %lu", f) {
+        TEST_DESC("index -100 from 500 list at fill %d", f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 500; i++)
                 quicklistPushTail(ql, f, genstr("hello", i + 1), 32);
@@ -1654,7 +1753,7 @@ int quicklistTest(int argc, char *argv[]) {
             quicklistRelease(ql);
         }
 
-        TEST_DESC("index too big +1 from 50 list at fill %lu", f) {
+        TEST_DESC("index too big +1 from 50 list at fill %d", f) {
             quicklist *ql = quicklistCreate();
             for (int i = 0; i < 50; i++)
                 quicklistPushTail(ql, f, genstr("hello", i + 1), 32);
@@ -1821,8 +1920,8 @@ int quicklistTest(int argc, char *argv[]) {
         OK;
     }
 
-    for (size_t f = 0; f < 16; f++) {
-        TEST_DESC("lrem test at fill %lu", f) {
+    for (int f = optimize_start; f < 16; f++) {
+        TEST_DESC("lrem test at fill %d", f) {
             quicklist *ql = quicklistCreate();
             char *words[] = { "abc", "foo", "bar",  "foobar", "foobared",
                               "zap", "bar", "test", "foo" };
@@ -1902,8 +2001,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 16; f++) {
-        TEST_DESC("iterate reverse + delete at fill %lu", f) {
+    for (int f = optimize_start; f < 16; f++) {
+        TEST_DESC("iterate reverse + delete at fill %d", f) {
             quicklist *ql = quicklistCreate();
             quicklistPushTail(ql, f, "abc", 3);
             quicklistPushTail(ql, f, "def", 3);
@@ -1940,8 +2039,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 800; f++) {
-        TEST_DESC("iterator at index test at fill %lu", f) {
+    for (int f = optimize_start; f < 800; f++) {
+        TEST_DESC("iterator at index test at fill %d", f) {
             quicklist *ql = quicklistCreate();
             char num[32];
             long long nums[5000];
@@ -1965,8 +2064,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 40; f++) {
-        TEST_DESC("ltrim test A at fill %lu", f) {
+    for (int f = optimize_start; f < 40; f++) {
+        TEST_DESC("ltrim test A at fill %d", f) {
             quicklist *ql = quicklistCreate();
             char num[32];
             long long nums[5000];
@@ -1993,8 +2092,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 40; f++) {
-        TEST_DESC("ltrim test B at fill %lu", f) {
+    for (int f = optimize_start; f < 40; f++) {
+        TEST_DESC("ltrim test B at fill %d", f) {
             quicklist *ql = quicklistCreate();
             char num[32];
             long long nums[5000];
@@ -2036,8 +2135,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 40; f++) {
-        TEST_DESC("ltrim test C at fill %lu", f) {
+    for (int f = optimize_start; f < 40; f++) {
+        TEST_DESC("ltrim test C at fill %d", f) {
             quicklist *ql = quicklistCreate();
             char num[32];
             long long nums[5000];
@@ -2063,8 +2162,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 40; f++) {
-        TEST_DESC("ltrim test D at fill %lu", f) {
+    for (int f = optimize_start; f < 40; f++) {
+        TEST_DESC("ltrim test D at fill %d", f) {
             quicklist *ql = quicklistCreate();
             char num[32];
             long long nums[5000];
@@ -2083,8 +2182,8 @@ int quicklistTest(int argc, char *argv[]) {
         }
     }
 
-    for (size_t f = 0; f < 72; f++) {
-        TEST_DESC("create quicklist from ziplist at fill %lu", f) {
+    for (int f = optimize_start; f < 72; f++) {
+        TEST_DESC("create quicklist from ziplist at fill %d", f) {
             unsigned char *zl = ziplistNew();
             long long nums[32];
             char num[32];