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
@@ -175,14 +148,12 @@ int dictExpand(dict *d, unsigned long size)
     if (dictIsRehashing(d) || d->ht[0].used > size)
         return DICT_ERR;
 
+    /* Allocate the new hashtable and initialize all pointers to NULL */
     n.size = realsize;
     n.sizemask = realsize-1;
-    n.table = _dictAlloc(realsize*sizeof(dictEntry*));
+    n.table = zcalloc(realsize*sizeof(dictEntry*));
     n.used = 0;
 
-    /* Initialize all the pointers to NULL */
-    memset(n.table, 0, realsize*sizeof(dictEntry*));
-
     /* Is this the first initialization? If so it's not really a rehashing
      * we just set the first hash table so that it can accept keys. */
     if (d->ht[0].table == NULL) {
@@ -208,7 +179,7 @@ int dictRehash(dict *d, int n) {
 
         /* Check if we already rehashed the whole table... */
         if (d->ht[0].used == 0) {
-            _dictFree(d->ht[0].table);
+            zfree(d->ht[0].table);
             d->ht[0] = d->ht[1];
             _dictReset(&d->ht[1]);
             d->rehashidx = -1;
@@ -285,7 +256,7 @@ int dictAdd(dict *d, void *key, void *val)
 
     /* Allocates the memory and stores key */
     ht = dictIsRehashing(d) ? &d->ht[1] : &d->ht[0];
-    entry = _dictAlloc(sizeof(*entry));
+    entry = zmalloc(sizeof(*entry));
     entry->next = ht->table[index];
     ht->table[index] = entry;
     ht->used++;
@@ -348,7 +319,7 @@ static int dictGenericDelete(dict *d, const void *key, int nofree)
                     dictFreeEntryKey(d, he);
                     dictFreeEntryVal(d, he);
                 }
-                _dictFree(he);
+                zfree(he);
                 d->ht[table].used--;
                 return DICT_OK;
             }
@@ -382,13 +353,13 @@ int _dictClear(dict *d, dictht *ht)
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
@@ -399,7 +370,7 @@ void dictRelease(dict *d)
 {
     _dictClear(d,&d->ht[0]);
     _dictClear(d,&d->ht[1]);
-    _dictFree(d);
+    zfree(d);
 }
 
 dictEntry *dictFind(dict *d, const void *key)
@@ -432,7 +403,7 @@ void *dictFetchValue(dict *d, const void *key) {
 
 dictIterator *dictGetIterator(dict *d)
 {
-    dictIterator *iter = _dictAlloc(sizeof(*iter));
+    dictIterator *iter = zmalloc(sizeof(*iter));
 
     iter->d = d;
     iter->table = 0;
@@ -475,7 +446,7 @@ dictEntry *dictNext(dictIterator *iter)
 void dictReleaseIterator(dictIterator *iter)
 {
     if (!(iter->index == -1 && iter->table == 0)) iter->d->iterators--;
-    _dictFree(iter);
+    zfree(iter);
 }
 
 /* Return a random entry from the hash table. Useful to
@@ -644,35 +615,30 @@ void dictDisableResize(void) {
     dict_can_resize = 0;
 }
 
+#if 0
+
+/* The following are just example hash table types implementations.
+ * Not useful for Redis so they are commented out.
+ */
+
 /* ----------------------- StringCopy Hash Table Type ------------------------*/
 
 static unsigned int _dictStringCopyHTHashFunction(const void *key)
 {
     return dictGenHashFunction(key, strlen(key));
 }
 
-static void *_dictStringCopyHTKeyDup(void *privdata, const void *key)
+static void *_dictStringDup(void *privdata, const void *key)
 {
     int len = strlen(key);
-    char *copy = _dictAlloc(len+1);
+    char *copy = zmalloc(len+1);
     DICT_NOTUSED(privdata);
 
     memcpy(copy, key, len);
     copy[len] = '\0';
     return copy;
 }
 
-static void *_dictStringKeyValCopyHTValDup(void *privdata, const void *val)
-{
-    int len = strlen(val);
-    char *copy = _dictAlloc(len+1);
-    DICT_NOTUSED(privdata);
-
-    memcpy(copy, val, len);
-    copy[len] = '\0';
-    return copy;
-}
-
 static int _dictStringCopyHTKeyCompare(void *privdata, const void *key1,
         const void *key2)
 {
@@ -681,47 +647,41 @@ static int _dictStringCopyHTKeyCompare(void *privdata, const void *key1,
     return strcmp(key1, key2) == 0;
 }
 
-static void _dictStringCopyHTKeyDestructor(void *privdata, void *key)
-{
-    DICT_NOTUSED(privdata);
-
-    _dictFree((void*)key); /* ATTENTION: const cast */
-}
-
-static void _dictStringKeyValCopyHTValDestructor(void *privdata, void *val)
+static void _dictStringDestructor(void *privdata, void *key)
 {
     DICT_NOTUSED(privdata);
 
-    _dictFree((void*)val); /* ATTENTION: const cast */
+    zfree(key);
 }
 
 dictType dictTypeHeapStringCopyKey = {
-    _dictStringCopyHTHashFunction,        /* hash function */
-    _dictStringCopyHTKeyDup,              /* key dup */
-    NULL,                               /* val dup */
-    _dictStringCopyHTKeyCompare,          /* key compare */
-    _dictStringCopyHTKeyDestructor,       /* key destructor */
-    NULL                                /* val destructor */
+    _dictStringCopyHTHashFunction, /* hash function */
+    _dictStringDup,                /* key dup */
+    NULL,                          /* val dup */
+    _dictStringCopyHTKeyCompare,   /* key compare */
+    _dictStringDestructor,         /* key destructor */
+    NULL                           /* val destructor */
 };
 
 /* This is like StringCopy but does not auto-duplicate the key.
  * It's used for intepreter's shared strings. */
 dictType dictTypeHeapStrings = {
-    _dictStringCopyHTHashFunction,        /* hash function */
-    NULL,                               /* key dup */
-    NULL,                               /* val dup */
-    _dictStringCopyHTKeyCompare,          /* key compare */
-    _dictStringCopyHTKeyDestructor,       /* key destructor */
-    NULL                                /* val destructor */
+    _dictStringCopyHTHashFunction, /* hash function */
+    NULL,                          /* key dup */
+    NULL,                          /* val dup */
+    _dictStringCopyHTKeyCompare,   /* key compare */
+    _dictStringDestructor,         /* key destructor */
+    NULL                           /* val destructor */
 };
 
 /* This is like StringCopy but also automatically handle dynamic
  * allocated C strings as values. */
 dictType dictTypeHeapStringCopyKeyValue = {
-    _dictStringCopyHTHashFunction,        /* hash function */
-    _dictStringCopyHTKeyDup,              /* key dup */
-    _dictStringKeyValCopyHTValDup,        /* val dup */
-    _dictStringCopyHTKeyCompare,          /* key compare */
-    _dictStringCopyHTKeyDestructor,       /* key destructor */
-    _dictStringKeyValCopyHTValDestructor, /* val destructor */
+    _dictStringCopyHTHashFunction, /* hash function */
+    _dictStringDup,                /* key dup */
+    _dictStringDup,                /* val dup */
+    _dictStringCopyHTKeyCompare,   /* key compare */
+    _dictStringDestructor,         /* key destructor */
+    _dictStringDestructor,         /* val destructor */
 };
+#endif