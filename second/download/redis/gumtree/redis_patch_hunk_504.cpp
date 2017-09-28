             he = he->next;
         }
         clvector[(chainlen < DICT_STATS_VECTLEN) ? chainlen : (DICT_STATS_VECTLEN-1)]++;
         if (chainlen > maxchainlen) maxchainlen = chainlen;
         totchainlen += chainlen;
     }
-    printf("Hash table stats:\n");
-    printf(" table size: %ld\n", ht->size);
-    printf(" number of elements: %ld\n", ht->used);
-    printf(" different slots: %ld\n", slots);
-    printf(" max chain length: %ld\n", maxchainlen);
-    printf(" avg chain length (counted): %.02f\n", (float)totchainlen/slots);
-    printf(" avg chain length (computed): %.02f\n", (float)ht->used/slots);
-    printf(" Chain length distribution:\n");
+
+    /* Generate human readable stats. */
+    l += snprintf(buf+l,bufsize-l,
+        "Hash table %d stats (%s):\n"
+        " table size: %ld\n"
+        " number of elements: %ld\n"
+        " different slots: %ld\n"
+        " max chain length: %ld\n"
+        " avg chain length (counted): %.02f\n"
+        " avg chain length (computed): %.02f\n"
+        " Chain length distribution:\n",
+        tableid, (tableid == 0) ? "main hash table" : "rehashing target",
+        ht->size, ht->used, slots, maxchainlen,
+        (float)totchainlen/slots, (float)ht->used/slots);
+
     for (i = 0; i < DICT_STATS_VECTLEN-1; i++) {
         if (clvector[i] == 0) continue;
-        printf("   %s%ld: %ld (%.02f%%)\n",(i == DICT_STATS_VECTLEN-1)?">= ":"", i, clvector[i], ((float)clvector[i]/ht->size)*100);
-    }
-}
-
-void dictPrintStats(dict *d) {
-    _dictPrintStatsHt(&d->ht[0]);
-    if (dictIsRehashing(d)) {
-        printf("-- Rehashing into ht[1]:\n");
-        _dictPrintStatsHt(&d->ht[1]);
+        if (l >= bufsize) break;
+        l += snprintf(buf+l,bufsize-l,
+            "   %s%ld: %ld (%.02f%%)\n",
+            (i == DICT_STATS_VECTLEN-1)?">= ":"",
+            i, clvector[i], ((float)clvector[i]/ht->size)*100);
+    }
+
+    /* Unlike snprintf(), teturn the number of characters actually written. */
+    if (bufsize) buf[bufsize-1] = '\0';
+    return strlen(buf);
+}
+
+void dictGetStats(char *buf, size_t bufsize, dict *d) {
+    size_t l;
+    char *orig_buf = buf;
+    size_t orig_bufsize = bufsize;
+
+    l = _dictGetStatsHt(buf,bufsize,&d->ht[0],0);
+    buf += l;
+    bufsize -= l;
+    if (dictIsRehashing(d) && bufsize > 0) {
+        _dictGetStatsHt(buf,bufsize,&d->ht[1],1);
     }
+    /* Make sure there is a NULL term at the end. */
+    if (orig_bufsize) orig_buf[orig_bufsize-1] = '\0';
 }
-
-/* ----------------------- StringCopy Hash Table Type ------------------------*/
-
-static unsigned int _dictStringCopyHTHashFunction(const void *key)
-{
-    return dictGenHashFunction(key, strlen(key));
-}
-
-static void *_dictStringDup(void *privdata, const void *key)
-{
-    int len = strlen(key);
-    char *copy = zmalloc(len+1);
-    DICT_NOTUSED(privdata);
-
-    memcpy(copy, key, len);
-    copy[len] = '\0';
-    return copy;
-}
-
-static int _dictStringCopyHTKeyCompare(void *privdata, const void *key1,
-        const void *key2)
-{
-    DICT_NOTUSED(privdata);
-
-    return strcmp(key1, key2) == 0;
-}
-
-static void _dictStringDestructor(void *privdata, void *key)
-{
-    DICT_NOTUSED(privdata);
-
-    zfree(key);
-}
-
-dictType dictTypeHeapStringCopyKey = {
-    _dictStringCopyHTHashFunction, /* hash function */
-    _dictStringDup,                /* key dup */
-    NULL,                          /* val dup */
-    _dictStringCopyHTKeyCompare,   /* key compare */
-    _dictStringDestructor,         /* key destructor */
-    NULL                           /* val destructor */
-};
-
-/* This is like StringCopy but does not auto-duplicate the key.
- * It's used for intepreter's shared strings. */
-dictType dictTypeHeapStrings = {
-    _dictStringCopyHTHashFunction, /* hash function */
-    NULL,                          /* key dup */
-    NULL,                          /* val dup */
-    _dictStringCopyHTKeyCompare,   /* key compare */
-    _dictStringDestructor,         /* key destructor */
-    NULL                           /* val destructor */
-};
-
-/* This is like StringCopy but also automatically handle dynamic
- * allocated C strings as values. */
-dictType dictTypeHeapStringCopyKeyValue = {
-    _dictStringCopyHTHashFunction, /* hash function */
-    _dictStringDup,                /* key dup */
-    _dictStringDup,                /* val dup */
-    _dictStringCopyHTKeyCompare,   /* key compare */
-    _dictStringDestructor,         /* key destructor */
-    _dictStringDestructor,         /* val destructor */
-};
-#endif
