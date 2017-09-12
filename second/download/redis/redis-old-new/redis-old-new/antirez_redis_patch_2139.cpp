@@ -119,7 +119,7 @@ unsigned int dictGenHashFunction(const unsigned char *buf, int len) {
 
 /* Reset an hashtable already initialized with ht_init().
  * NOTE: This function should only called by ht_destroy(). */
-static void _dictReset(dict *ht)
+static void _dictReset(dictht *ht)
 {
     ht->table = NULL;
     ht->size = 0;
@@ -131,163 +131,211 @@ static void _dictReset(dict *ht)
 dict *dictCreate(dictType *type,
         void *privDataPtr)
 {
-    dict *ht = _dictAlloc(sizeof(*ht));
+    dict *d = _dictAlloc(sizeof(*d));
 
-    _dictInit(ht,type,privDataPtr);
-    return ht;
+    _dictInit(d,type,privDataPtr);
+    return d;
 }
 
 /* Initialize the hash table */
-int _dictInit(dict *ht, dictType *type,
+int _dictInit(dict *d, dictType *type,
         void *privDataPtr)
 {
-    _dictReset(ht);
-    ht->type = type;
-    ht->privdata = privDataPtr;
+    _dictReset(&d->ht[0]);
+    _dictReset(&d->ht[1]);
+    d->type = type;
+    d->privdata = privDataPtr;
+    d->rehashidx = -1;
+    d->iterators = 0;
     return DICT_OK;
 }
 
 /* Resize the table to the minimal size that contains all the elements,
  * but with the invariant of a USER/BUCKETS ration near to <= 1 */
-int dictResize(dict *ht)
+int dictResize(dict *d)
 {
-    int minimal = ht->used;
+    int minimal;
 
-    if (!dict_can_resize) return DICT_ERR;
+    if (!dict_can_resize || dictIsRehashing(d)) return DICT_ERR;
+    minimal = d->ht[0].used;
     if (minimal < DICT_HT_INITIAL_SIZE)
         minimal = DICT_HT_INITIAL_SIZE;
-    return dictExpand(ht, minimal);
+    return dictExpand(d, minimal);
 }
 
 /* Expand or create the hashtable */
-int dictExpand(dict *ht, unsigned long size)
+int dictExpand(dict *d, unsigned long size)
 {
-    dict n; /* the new hashtable */
-    unsigned long realsize = _dictNextPower(size), i;
+    dictht n; /* the new hashtable */
+    unsigned long realsize = _dictNextPower(size);
 
     /* the size is invalid if it is smaller than the number of
      * elements already inside the hashtable */
-    if (ht->used > size)
+    if (dictIsRehashing(d) || d->ht[0].used > size)
         return DICT_ERR;
 
-    _dictInit(&n, ht->type, ht->privdata);
     n.size = realsize;
     n.sizemask = realsize-1;
     n.table = _dictAlloc(realsize*sizeof(dictEntry*));
+    n.used = 0;
 
     /* Initialize all the pointers to NULL */
     memset(n.table, 0, realsize*sizeof(dictEntry*));
 
-    /* Copy all the elements from the old to the new table:
-     * note that if the old hash table is empty ht->size is zero,
-     * so dictExpand just creates an hash table. */
-    n.used = ht->used;
-    for (i = 0; i < ht->size && ht->used > 0; i++) {
-        dictEntry *he, *nextHe;
+    /* Is this the first initialization? If so it's not really a rehashing
+     * we just set the first hash table so that it can accept keys. */
+    if (d->ht[0].table == NULL) {
+        d->ht[0] = n;
+        return DICT_OK;
+    }
 
-        if (ht->table[i] == NULL) continue;
-        
-        /* For each hash entry on this slot... */
-        he = ht->table[i];
-        while(he) {
+    /* Prepare a second hash table for incremental rehashing */
+    d->ht[1] = n;
+    d->rehashidx = 0;
+    return DICT_OK;
+}
+
+/* Performs N steps of incremental rehashing. Returns 1 if there are still
+ * keys to move from the old to the new hash table, otherwise 0 is returned.
+ * Note that a rehashing step consists in moving a bucket (that may have more
+ * thank one key as we use chaining) from the old to the new hash table. */
+int dictRehash(dict *d, int n) {
+    if (!dictIsRehashing(d)) return 0;
+
+    while(n--) {
+        dictEntry *de, *nextde;
+
+        /* Check if we already rehashed the whole table... */
+        if (d->ht[0].used == 0) {
+            _dictFree(d->ht[0].table);
+            d->ht[0] = d->ht[1];
+            _dictReset(&d->ht[1]);
+            d->rehashidx = -1;
+            return 0;
+        }
+
+        /* Note that rehashidx can't overflow as we are sure there are more
+         * elements because ht[0].used != 0 */
+        while(d->ht[0].table[d->rehashidx] == NULL) d->rehashidx++;
+        de = d->ht[0].table[d->rehashidx];
+        /* Move all the keys in this bucket from the old to the new hash HT */
+        while(de) {
             unsigned int h;
 
-            nextHe = he->next;
-            /* Get the new element index */
-            h = dictHashKey(ht, he->key) & n.sizemask;
-            he->next = n.table[h];
-            n.table[h] = he;
-            ht->used--;
-            /* Pass to the next element */
-            he = nextHe;
+            nextde = de->next;
+            /* Get the index in the new hash table */
+            h = dictHashKey(d, de->key) & d->ht[1].sizemask;
+            de->next = d->ht[1].table[h];
+            d->ht[1].table[h] = de;
+            d->ht[0].used--;
+            d->ht[1].used++;
+            de = nextde;
         }
+        d->ht[0].table[d->rehashidx] = NULL;
+        d->rehashidx++;
     }
-    assert(ht->used == 0);
-    _dictFree(ht->table);
+    return 1;
+}
 
-    /* Remap the new hashtable in the old */
-    *ht = n;
-    return DICT_OK;
+/* This function performs just a step of rehashing, and only if there are
+ * not iterators bound to our hash table. When we have iterators in the middle
+ * of a rehashing we can't mess with the two hash tables otherwise some element
+ * can be missed or duplicated.
+ *
+ * This function is called by common lookup or update operations in the
+ * dictionary so that the hash table automatically migrates from H1 to H2
+ * while it is actively used. */
+static void _dictRehashStep(dict *d) {
+    if (d->iterators == 0) dictRehash(d,1);
 }
 
 /* Add an element to the target hash table */
-int dictAdd(dict *ht, void *key, void *val)
+int dictAdd(dict *d, void *key, void *val)
 {
     int index;
     dictEntry *entry;
+    dictht *ht;
+
+    if (dictIsRehashing(d)) _dictRehashStep(d);
 
     /* Get the index of the new element, or -1 if
      * the element already exists. */
-    if ((index = _dictKeyIndex(ht, key)) == -1)
+    if ((index = _dictKeyIndex(d, key)) == -1)
         return DICT_ERR;
 
     /* Allocates the memory and stores key */
+    ht = dictIsRehashing(d) ? &d->ht[1] : &d->ht[0];
     entry = _dictAlloc(sizeof(*entry));
     entry->next = ht->table[index];
     ht->table[index] = entry;
+    ht->used++;
 
     /* Set the hash entry fields. */
-    dictSetHashKey(ht, entry, key);
-    dictSetHashVal(ht, entry, val);
-    ht->used++;
+    dictSetHashKey(d, entry, key);
+    dictSetHashVal(d, entry, val);
     return DICT_OK;
 }
 
 /* Add an element, discarding the old if the key already exists.
  * Return 1 if the key was added from scratch, 0 if there was already an
  * element with such key and dictReplace() just performed a value update
  * operation. */
-int dictReplace(dict *ht, void *key, void *val)
+int dictReplace(dict *d, void *key, void *val)
 {
     dictEntry *entry, auxentry;
 
     /* Try to add the element. If the key
      * does not exists dictAdd will suceed. */
-    if (dictAdd(ht, key, val) == DICT_OK)
+    if (dictAdd(d, key, val) == DICT_OK)
         return 1;
     /* It already exists, get the entry */
-    entry = dictFind(ht, key);
+    entry = dictFind(d, key);
     /* Free the old value and set the new one */
     /* Set the new value and free the old one. Note that it is important
      * to do that in this order, as the value may just be exactly the same
      * as the previous one. In this context, think to reference counting,
      * you want to increment (set), and then decrement (free), and not the
      * reverse. */
     auxentry = *entry;
-    dictSetHashVal(ht, entry, val);
-    dictFreeEntryVal(ht, &auxentry);
+    dictSetHashVal(d, entry, val);
+    dictFreeEntryVal(d, &auxentry);
     return 0;
 }
 
 /* Search and remove an element */
-static int dictGenericDelete(dict *ht, const void *key, int nofree)
+static int dictGenericDelete(dict *d, const void *key, int nofree)
 {
-    unsigned int h;
+    unsigned int h, idx;
     dictEntry *he, *prevHe;
+    int table;
 
-    if (ht->size == 0)
-        return DICT_ERR;
-    h = dictHashKey(ht, key) & ht->sizemask;
-    he = ht->table[h];
+    if (d->ht[0].size == 0) return DICT_ERR; /* d->ht[0].table is NULL */
+    if (dictIsRehashing(d)) _dictRehashStep(d);
+    h = dictHashKey(d, key);
 
-    prevHe = NULL;
-    while(he) {
-        if (dictCompareHashKeys(ht, key, he->key)) {
-            /* Unlink the element from the list */
-            if (prevHe)
-                prevHe->next = he->next;
-            else
-                ht->table[h] = he->next;
-            if (!nofree) {
-                dictFreeEntryKey(ht, he);
-                dictFreeEntryVal(ht, he);
+    for (table = 0; table <= 1; table++) {
+        idx = h & d->ht[table].sizemask;
+        he = d->ht[table].table[idx];
+        prevHe = NULL;
+        while(he) {
+            if (dictCompareHashKeys(d, key, he->key)) {
+                /* Unlink the element from the list */
+                if (prevHe)
+                    prevHe->next = he->next;
+                else
+                    d->ht[table].table[idx] = he->next;
+                if (!nofree) {
+                    dictFreeEntryKey(d, he);
+                    dictFreeEntryVal(d, he);
+                }
+                _dictFree(he);
+                d->ht[table].used--;
+                return DICT_OK;
             }
-            _dictFree(he);
-            ht->used--;
-            return DICT_OK;
+            prevHe = he;
+            he = he->next;
         }
-        prevHe = he;
-        he = he->next;
+        if (!dictIsRehashing(d)) break;
     }
     return DICT_ERR; /* not found */
 }
@@ -300,8 +348,8 @@ int dictDeleteNoFree(dict *ht, const void *key) {
     return dictGenericDelete(ht,key,1);
 }
 
-/* Destroy an entire hash table */
-int _dictClear(dict *ht)
+/* Destroy an entire dictionary */
+int _dictClear(dict *d, dictht *ht)
 {
     unsigned long i;
 
@@ -312,8 +360,8 @@ int _dictClear(dict *ht)
         if ((he = ht->table[i]) == NULL) continue;
         while(he) {
             nextHe = he->next;
-            dictFreeEntryKey(ht, he);
-            dictFreeEntryVal(ht, he);
+            dictFreeEntryKey(d, he);
+            dictFreeEntryVal(d, he);
             _dictFree(he);
             ht->used--;
             he = nextHe;
@@ -327,33 +375,40 @@ int _dictClear(dict *ht)
 }
 
 /* Clear & Release the hash table */
-void dictRelease(dict *ht)
+void dictRelease(dict *d)
 {
-    _dictClear(ht);
-    _dictFree(ht);
+    _dictClear(d,&d->ht[0]);
+    _dictClear(d,&d->ht[1]);
+    _dictFree(d);
 }
 
-dictEntry *dictFind(dict *ht, const void *key)
+dictEntry *dictFind(dict *d, const void *key)
 {
     dictEntry *he;
-    unsigned int h;
-
-    if (ht->size == 0) return NULL;
-    h = dictHashKey(ht, key) & ht->sizemask;
-    he = ht->table[h];
-    while(he) {
-        if (dictCompareHashKeys(ht, key, he->key))
-            return he;
-        he = he->next;
+    unsigned int h, idx, table;
+
+    if (d->ht[0].size == 0) return NULL; /* We don't have a table at all */
+    if (dictIsRehashing(d)) _dictRehashStep(d);
+    h = dictHashKey(d, key);
+    for (table = 0; table <= 1; table++) {
+        idx = h & d->ht[table].sizemask;
+        he = d->ht[table].table[idx];
+        while(he) {
+            if (dictCompareHashKeys(d, key, he->key))
+                return he;
+            he = he->next;
+        }
+        if (!dictIsRehashing(d)) return NULL;
     }
     return NULL;
 }
 
-dictIterator *dictGetIterator(dict *ht)
+dictIterator *dictGetIterator(dict *d)
 {
     dictIterator *iter = _dictAlloc(sizeof(*iter));
 
-    iter->ht = ht;
+    iter->d = d;
+    iter->table = 0;
     iter->index = -1;
     iter->entry = NULL;
     iter->nextEntry = NULL;
@@ -364,10 +419,19 @@ dictEntry *dictNext(dictIterator *iter)
 {
     while (1) {
         if (iter->entry == NULL) {
+            dictht *ht = &iter->d->ht[iter->table];
+            if (iter->index == -1 && iter->table == 0) iter->d->iterators++;
             iter->index++;
-            if (iter->index >=
-                    (signed)iter->ht->size) break;
-            iter->entry = iter->ht->table[iter->index];
+            if (iter->index >= (signed) ht->size) {
+                if (dictIsRehashing(iter->d) && iter->table == 0) {
+                    iter->table++;
+                    iter->index = 0;
+                    ht = &iter->d->ht[1];
+                } else {
+                    break;
+                }
+            }
+            iter->entry = ht->table[iter->index];
         } else {
             iter->entry = iter->nextEntry;
         }
@@ -383,49 +447,62 @@ dictEntry *dictNext(dictIterator *iter)
 
 void dictReleaseIterator(dictIterator *iter)
 {
+    if (!(iter->index == -1 && iter->table == 0)) iter->d->iterators--;
     _dictFree(iter);
 }
 
 /* Return a random entry from the hash table. Useful to
  * implement randomized algorithms */
-dictEntry *dictGetRandomKey(dict *ht)
+dictEntry *dictGetRandomKey(dict *d)
 {
-    dictEntry *he;
+    dictEntry *he, *orighe;
     unsigned int h;
     int listlen, listele;
 
-    if (ht->used == 0) return NULL;
-    do {
-        h = random() & ht->sizemask;
-        he = ht->table[h];
-    } while(he == NULL);
+    if (dictSize(d) == 0) return NULL;
+    if (dictIsRehashing(d)) _dictRehashStep(d);
+    if (dictIsRehashing(d)) {
+        do {
+            h = random() % (d->ht[0].size+d->ht[1].size);
+            he = (h >= d->ht[0].size) ? d->ht[1].table[h - d->ht[0].size] :
+                                      d->ht[0].table[h];
+        } while(he == NULL);
+    } else {
+        do {
+            h = random() & d->ht[0].sizemask;
+            he = d->ht[0].table[h];
+        } while(he == NULL);
+    }
 
     /* Now we found a non empty bucket, but it is a linked
      * list and we need to get a random element from the list.
-     * The only sane way to do so is to count the element and
+     * The only sane way to do so is counting the elements and
      * select a random index. */
     listlen = 0;
+    orighe = he;
     while(he) {
         he = he->next;
         listlen++;
     }
     listele = random() % listlen;
-    he = ht->table[h];
+    he = orighe;
     while(listele--) he = he->next;
     return he;
 }
 
 /* ------------------------- private functions ------------------------------ */
 
 /* Expand the hash table if needed */
-static int _dictExpandIfNeeded(dict *ht)
+static int _dictExpandIfNeeded(dict *d)
 {
     /* If the hash table is empty expand it to the intial size,
      * if the table is "full" dobule its size. */
-    if (ht->size == 0)
-        return dictExpand(ht, DICT_HT_INITIAL_SIZE);
-    if (ht->used >= ht->size && dict_can_resize)
-        return dictExpand(ht, ((ht->size > ht->used) ? ht->size : ht->used)*2);
+    if (dictIsRehashing(d)) return DICT_OK;
+    if (d->ht[0].size == 0)
+        return dictExpand(d, DICT_HT_INITIAL_SIZE);
+    if (d->ht[0].used >= d->ht[0].size && dict_can_resize)
+        return dictExpand(d, ((d->ht[0].size > d->ht[0].used) ?
+                                    d->ht[0].size : d->ht[0].used)*2);
     return DICT_OK;
 }
 
@@ -444,33 +521,49 @@ static unsigned long _dictNextPower(unsigned long size)
 
 /* Returns the index of a free slot that can be populated with
  * an hash entry for the given 'key'.
- * If the key already exists, -1 is returned. */
-static int _dictKeyIndex(dict *ht, const void *key)
+ * If the key already exists, -1 is returned.
+ *
+ * Note that if we are in the process of rehashing the hash table, the
+ * index is always returned in the context of the second (new) hash table. */
+static int _dictKeyIndex(dict *d, const void *key)
 {
-    unsigned int h;
+    unsigned int h, h1, h2;
     dictEntry *he;
 
     /* Expand the hashtable if needed */
-    if (_dictExpandIfNeeded(ht) == DICT_ERR)
+    if (_dictExpandIfNeeded(d) == DICT_ERR)
         return -1;
     /* Compute the key hash value */
-    h = dictHashKey(ht, key) & ht->sizemask;
+    h = dictHashKey(d, key);
+    h1 = h & d->ht[0].sizemask;
+    h2 = h & d->ht[1].sizemask;
     /* Search if this slot does not already contain the given key */
-    he = ht->table[h];
+    he = d->ht[0].table[h1];
+    while(he) {
+        if (dictCompareHashKeys(d, key, he->key))
+            return -1;
+        he = he->next;
+    }
+    if (!dictIsRehashing(d)) return h1;
+    /* Check the second hash table */
+    he = d->ht[1].table[h2];
     while(he) {
-        if (dictCompareHashKeys(ht, key, he->key))
+        if (dictCompareHashKeys(d, key, he->key))
             return -1;
         he = he->next;
     }
-    return h;
+    return h2;
 }
 
-void dictEmpty(dict *ht) {
-    _dictClear(ht);
+void dictEmpty(dict *d) {
+    _dictClear(d,&d->ht[0]);
+    _dictClear(d,&d->ht[1]);
+    d->rehashidx = -1;
+    d->iterators = 0;
 }
 
 #define DICT_STATS_VECTLEN 50
-void dictPrintStats(dict *ht) {
+static void _dictPrintStatsHt(dictht *ht) {
     unsigned long i, slots = 0, chainlen, maxchainlen = 0;
     unsigned long totchainlen = 0;
     unsigned long clvector[DICT_STATS_VECTLEN];
@@ -514,6 +607,14 @@ void dictPrintStats(dict *ht) {
     }
 }
 
+void dictPrintStats(dict *d) {
+    _dictPrintStatsHt(&d->ht[0]);
+    if (dictIsRehashing(d)) {
+        printf("-- Rehashing into ht[1]:\n");
+        _dictPrintStatsHt(&d->ht[1]);
+    }
+}
+
 void dictEnableResize(void) {
     dict_can_resize = 1;
 }