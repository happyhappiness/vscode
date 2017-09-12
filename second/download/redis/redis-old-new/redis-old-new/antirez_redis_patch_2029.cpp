@@ -52,33 +52,6 @@
  * around when there is a child performing saving operations. */
 static int dict_can_resize = 1;
 
-/* ---------------------------- Utility funcitons --------------------------- */
-
-static void _dictPanic(const char *fmt, ...)
-{
-    va_list ap;
-
-    va_start(ap, fmt);
-    fprintf(stderr, "\nDICT LIBRARY PANIC: ");
-    vfprintf(stderr, fmt, ap);
-    fprintf(stderr, "\n\n");
-    va_end(ap);
-}
-
-/* ------------------------- Heap Management Wrappers------------------------ */
-
-static void *_dictAlloc(size_t size)
-{
-    void *p = zmalloc(size);
-    if (p == NULL)
-        _dictPanic("Out of memory");
-    return p;
-}
-
-static void _dictFree(void *ptr) {
-    zfree(ptr);
-}
-
 /* -------------------------- private prototypes ---------------------------- */
 
 static int _dictExpandIfNeeded(dict *ht);
@@ -132,7 +105,7 @@ static void _dictReset(dictht *ht)
 dict *dictCreate(dictType *type,
         void *privDataPtr)
 {
-    dict *d = _dictAlloc(sizeof(*d));
+    dict *d = zmalloc(sizeof(*d));
 
     _dictInit(d,type,privDataPtr);
     return d;
@@ -177,7 +150,7 @@ int dictExpand(dict *d, unsigned long size)
 
     n.size = realsize;
     n.sizemask = realsize-1;
-    n.table = _dictAlloc(realsize*sizeof(dictEntry*));
+    n.table = zmalloc(realsize*sizeof(dictEntry*));
     n.used = 0;
 
     /* Initialize all the pointers to NULL */
@@ -208,7 +181,7 @@ int dictRehash(dict *d, int n) {
 
         /* Check if we already rehashed the whole table... */
         if (d->ht[0].used == 0) {
-            _dictFree(d->ht[0].table);
+            zfree(d->ht[0].table);
             d->ht[0] = d->ht[1];
             _dictReset(&d->ht[1]);
             d->rehashidx = -1;
@@ -285,7 +258,7 @@ int dictAdd(dict *d, void *key, void *val)
 
     /* Allocates the memory and stores key */
     ht = dictIsRehashing(d) ? &d->ht[1] : &d->ht[0];
-    entry = _dictAlloc(sizeof(*entry));
+    entry = zmalloc(sizeof(*entry));
     entry->next = ht->table[index];
     ht->table[index] = entry;
     ht->used++;
@@ -348,7 +321,7 @@ static int dictGenericDelete(dict *d, const void *key, int nofree)
                     dictFreeEntryKey(d, he);
                     dictFreeEntryVal(d, he);
                 }
-                _dictFree(he);
+                zfree(he);
                 d->ht[table].used--;
                 return DICT_OK;
             }
@@ -382,13 +355,13 @@ int _dictClear(dict *d, dictht *ht)
             nextHe = he->next;
             dictFreeEntryKey(d, he);
             dictFreeEntryVal(d, he);
-            _dictFree(he);
+            zfree(he);
             ht->used--;
             he = nextHe;
         }
     }
     /* Free the table and the allocated cache structure */
-    _dictFree(ht->table);
+    zfree(ht->table);
     /* Re-initialize the table */
     _dictReset(ht);
     return DICT_OK; /* never fails */
@@ -399,7 +372,7 @@ void dictRelease(dict *d)
 {
     _dictClear(d,&d->ht[0]);
     _dictClear(d,&d->ht[1]);
-    _dictFree(d);
+    zfree(d);
 }
 
 dictEntry *dictFind(dict *d, const void *key)
@@ -432,7 +405,7 @@ void *dictFetchValue(dict *d, const void *key) {
 
 dictIterator *dictGetIterator(dict *d)
 {
-    dictIterator *iter = _dictAlloc(sizeof(*iter));
+    dictIterator *iter = zmalloc(sizeof(*iter));
 
     iter->d = d;
     iter->table = 0;
@@ -475,7 +448,7 @@ dictEntry *dictNext(dictIterator *iter)
 void dictReleaseIterator(dictIterator *iter)
 {
     if (!(iter->index == -1 && iter->table == 0)) iter->d->iterators--;
-    _dictFree(iter);
+    zfree(iter);
 }
 
 /* Return a random entry from the hash table. Useful to
@@ -654,7 +627,7 @@ static unsigned int _dictStringCopyHTHashFunction(const void *key)
 static void *_dictStringDup(void *privdata, const void *key)
 {
     int len = strlen(key);
-    char *copy = _dictAlloc(len+1);
+    char *copy = zmalloc(len+1);
     DICT_NOTUSED(privdata);
 
     memcpy(copy, key, len);
@@ -674,7 +647,7 @@ static void _dictStringDestructor(void *privdata, void *key)
 {
     DICT_NOTUSED(privdata);
 
-    _dictFree(key);
+    zfree(key);
 }
 
 dictType dictTypeHeapStringCopyKey = {