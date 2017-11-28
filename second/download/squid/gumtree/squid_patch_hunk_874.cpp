     const cache_key *newkey;
 
     if (key && EBIT_TEST(flags, KEY_PRIVATE))
         return;                 /* is already private */
 
     if (key) {
+        setReleaseFlag(); // will markForUnlink(); all caches/workers will know
+
+        // TODO: move into SwapDir::markForUnlink() already called by Root()
         if (swap_filen > -1)
             storeDirSwapLog(this, SWAP_LOG_DEL);
 
         hashDelete();
     }
 
-    if (mem_obj != NULL) {
+    if (mem_obj && mem_obj->hasUris()) {
         mem_obj->id = getKeyCounter();
-        newkey = storeKeyPrivate(mem_obj->url, mem_obj->method, mem_obj->id);
+        newkey = storeKeyPrivate(mem_obj->storeId(), mem_obj->method, mem_obj->id);
     } else {
         newkey = storeKeyPrivate("JUNK", Http::METHOD_NONE, getKeyCounter());
     }
 
     assert(hash_lookup(store_table, newkey) == NULL);
     EBIT_SET(flags, KEY_PRIVATE);
     hashInsert(newkey);
 }
 
 void
-StoreEntry::setPublicKey()
+StoreEntry::setPublicKey(const KeyScope scope)
 {
-    StoreEntry *e2 = NULL;
-    const cache_key *newkey;
-
     if (key && !EBIT_TEST(flags, KEY_PRIVATE))
         return;                 /* is already public */
 
     assert(mem_obj);
 
     /*
      * We can't make RELEASE_REQUEST objects public.  Depending on
      * when RELEASE_REQUEST gets set, we might not be swapping out
      * the object.  If we're not swapping out, then subsequent
      * store clients won't be able to access object data which has
      * been freed from memory.
      *
-     * If RELEASE_REQUEST is set, then ENTRY_CACHABLE should not
-     * be set, and StoreEntry::setPublicKey() should not be called.
+     * If RELEASE_REQUEST is set, setPublicKey() should not be called.
      */
 #if MORE_DEBUG_OUTPUT
 
     if (EBIT_TEST(flags, RELEASE_REQUEST))
         debugs(20, DBG_IMPORTANT, "assertion failed: RELEASE key " << key << ", url " << mem_obj->url);
 
 #endif
 
     assert(!EBIT_TEST(flags, RELEASE_REQUEST));
 
-    if (mem_obj->request) {
-        HttpRequest *request = mem_obj->request;
+    adjustVary();
+    forcePublicKey(calcPublicKey(scope));
+}
 
-        if (!mem_obj->vary_headers) {
-            /* First handle the case where the object no longer varies */
-            safe_free(request->vary_headers);
-        } else {
-            if (request->vary_headers && strcmp(request->vary_headers, mem_obj->vary_headers) != 0) {
-                /* Oops.. the variance has changed. Kill the base object
-                 * to record the new variance key
-                 */
-                safe_free(request->vary_headers);       /* free old "bad" variance key */
-                StoreEntry *pe = storeGetPublic(mem_obj->url, mem_obj->method);
+void
+StoreEntry::clearPublicKeyScope()
+{
+    if (!key || EBIT_TEST(flags, KEY_PRIVATE))
+        return; // probably the old public key was deleted or made private
 
-                if (pe)
-                    pe->release();
-            }
+    // TODO: adjustVary() when collapsed revalidation supports that
 
-            /* Make sure the request knows the variance status */
-            if (!request->vary_headers) {
-                const char *vary = httpMakeVaryMark(request, mem_obj->getReply());
+    const cache_key *newKey = calcPublicKey(ksDefault);
+    if (!storeKeyHashCmp(key, newKey))
+        return; // probably another collapsed revalidation beat us to this change
 
-                if (vary)
-                    request->vary_headers = xstrdup(vary);
-            }
-        }
+    forcePublicKey(newKey);
+}
 
-        // TODO: storeGetPublic() calls below may create unlocked entries.
-        // We should add/use storeHas() API or lock/unlock those entries.
-        if (mem_obj->vary_headers && !storeGetPublic(mem_obj->url, mem_obj->method)) {
-            /* Create "vary" base object */
-            String vary;
-            StoreEntry *pe = storeCreateEntry(mem_obj->url, mem_obj->log_url, request->flags, request->method);
-            /* We are allowed to do this typecast */
-            HttpReply *rep = new HttpReply;
-            rep->setHeaders(Http::scOkay, "Internal marker object", "x-squid-internal/vary", -1, -1, squid_curtime + 100000);
-            vary = mem_obj->getReply()->header.getList(HDR_VARY);
-
-            if (vary.size()) {
-                /* Again, we own this structure layout */
-                rep->header.putStr(HDR_VARY, vary.termedBuf());
-                vary.clean();
-            }
+/// Unconditionally sets public key for this store entry.
+/// Releases the old entry with the same public key (if any).
+void
+StoreEntry::forcePublicKey(const cache_key *newkey)
+{
+    if (StoreEntry *e2 = (StoreEntry *)hash_lookup(store_table, newkey)) {
+        assert(e2 != this);
+        debugs(20, 3, "Making old " << *e2 << " private.");
+        e2->setPrivateKey();
+        e2->release();
+    }
 
-#if X_ACCELERATOR_VARY
-            vary = mem_obj->getReply()->header.getList(HDR_X_ACCELERATOR_VARY);
+    if (key)
+        hashDelete();
 
-            if (vary.defined()) {
-                /* Again, we own this structure layout */
-                rep->header.putStr(HDR_X_ACCELERATOR_VARY, vary.termedBuf());
-                vary.clean();
-            }
+    EBIT_CLR(flags, KEY_PRIVATE);
 
-#endif
-            pe->replaceHttpReply(rep, false); // no write until key is public
+    hashInsert(newkey);
+
+    if (swap_filen > -1)
+        storeDirSwapLog(this, SWAP_LOG_ADD);
+}
 
-            pe->timestampsSet();
+/// Calculates correct public key for feeding forcePublicKey().
+/// Assumes adjustVary() has been called for this entry already.
+const cache_key *StoreEntry::calcPublicKey(const KeyScope keyScope) {
+    assert(mem_obj);
+    return mem_obj->request ?  storeKeyPublicByRequest(mem_obj->request, keyScope) :
+           storeKeyPublic(mem_obj->storeId(), mem_obj->method, keyScope);
+}
 
-            pe->makePublic();
+/// Updates mem_obj->request->vary_headers to reflect the current Vary.
+/// The vary_headers field is used to calculate the Vary marker key.
+/// Releases the old Vary marker with an outdated key (if any).
+void StoreEntry::adjustVary() {
+    assert(mem_obj);
 
-            pe->startWriting(); // after makePublic()
+    if (!mem_obj->request)
+        return;
 
-            pe->complete();
+    HttpRequest *request = mem_obj->request;
 
-            pe->unlock();
+    if (mem_obj->vary_headers.isEmpty()) {
+        /* First handle the case where the object no longer varies */
+        request->vary_headers.clear();
+    } else {
+        if (!request->vary_headers.isEmpty() && request->vary_headers.cmp(mem_obj->vary_headers) != 0) {
+            /* Oops.. the variance has changed. Kill the base object
+             * to record the new variance key
+             */
+            request->vary_headers.clear();       /* free old "bad" variance key */
+            if (StoreEntry *pe = storeGetPublic(mem_obj->storeId(), mem_obj->method))
+                pe->release();
         }
 
-        newkey = storeKeyPublicByRequest(mem_obj->request);
-    } else
-        newkey = storeKeyPublic(mem_obj->url, mem_obj->method);
+        /* Make sure the request knows the variance status */
+        if (request->vary_headers.isEmpty())
+            request->vary_headers = httpMakeVaryMark(request, mem_obj->getReply());
+    }
+
+    // TODO: storeGetPublic() calls below may create unlocked entries.
+    // We should add/use storeHas() API or lock/unlock those entries.
+    if (!mem_obj->vary_headers.isEmpty() && !storeGetPublic(mem_obj->storeId(), mem_obj->method)) {
+        /* Create "vary" base object */
+        String vary;
+        StoreEntry *pe = storeCreateEntry(mem_obj->storeId(), mem_obj->logUri(), request->flags, request->method);
+        /* We are allowed to do this typecast */
+        HttpReply *rep = new HttpReply;
+        rep->setHeaders(Http::scOkay, "Internal marker object", "x-squid-internal/vary", -1, -1, squid_curtime + 100000);
+        vary = mem_obj->getReply()->header.getList(HDR_VARY);
+
+        if (vary.size()) {
+            /* Again, we own this structure layout */
+            rep->header.putStr(HDR_VARY, vary.termedBuf());
+            vary.clean();
+        }
 
-    if ((e2 = (StoreEntry *) hash_lookup(store_table, newkey))) {
-        debugs(20, 3, "StoreEntry::setPublicKey: Making old '" << mem_obj->url << "' private.");
-        e2->setPrivateKey();
-        e2->release();
+#if X_ACCELERATOR_VARY
+        vary = mem_obj->getReply()->header.getList(HDR_X_ACCELERATOR_VARY);
 
-        if (mem_obj->request)
-            newkey = storeKeyPublicByRequest(mem_obj->request);
-        else
-            newkey = storeKeyPublic(mem_obj->url, mem_obj->method);
-    }
+        if (vary.size() > 0) {
+            /* Again, we own this structure layout */
+            rep->header.putStr(HDR_X_ACCELERATOR_VARY, vary.termedBuf());
+            vary.clean();
+        }
 
-    if (key)
-        hashDelete();
+#endif
+        pe->replaceHttpReply(rep, false); // no write until key is public
 
-    EBIT_CLR(flags, KEY_PRIVATE);
+        pe->timestampsSet();
 
-    hashInsert(newkey);
+        pe->makePublic();
 
-    if (swap_filen > -1)
-        storeDirSwapLog(this, SWAP_LOG_ADD);
+        pe->startWriting(); // after makePublic()
+
+        pe->complete();
+
+        pe->unlock("StoreEntry::forcePublicKey+Vary");
+    }
 }
 
 StoreEntry *
-storeCreateEntry(const char *url, const char *log_url, const RequestFlags &flags, const HttpRequestMethod& method)
+storeCreatePureEntry(const char *url, const char *log_url, const RequestFlags &flags, const HttpRequestMethod& method)
 {
     StoreEntry *e = NULL;
-    MemObject *mem = NULL;
     debugs(20, 3, "storeCreateEntry: '" << url << "'");
 
-    e = new StoreEntry(url, log_url);
-    e->lock_count = 1;          /* Note lock here w/o calling storeLock() */
-    mem = e->mem_obj;
-    mem->method = method;
-
-    if (neighbors_do_private_keys || !flags.hierarchical)
-        e->setPrivateKey();
-    else
-        e->setPublicKey();
+    e = new StoreEntry();
+    e->makeMemObject();
+    e->mem_obj->setUris(url, log_url, method);
 
     if (flags.cachable) {
-        EBIT_SET(e->flags, ENTRY_CACHABLE);
         EBIT_CLR(e->flags, RELEASE_REQUEST);
     } else {
-        /* StoreEntry::releaseRequest() clears ENTRY_CACHABLE */
         e->releaseRequest();
     }
 
     e->store_status = STORE_PENDING;
-    e->setMemStatus(NOT_IN_MEMORY);
     e->refcount = 0;
     e->lastref = squid_curtime;
     e->timestamp = -1;          /* set in StoreEntry::timestampsSet() */
     e->ping_status = PING_NONE;
     EBIT_SET(e->flags, ENTRY_VALIDATED);
     return e;
 }
 
+StoreEntry *
+storeCreateEntry(const char *url, const char *logUrl, const RequestFlags &flags, const HttpRequestMethod& method)
+{
+    StoreEntry *e = storeCreatePureEntry(url, logUrl, flags, method);
+    e->lock("storeCreateEntry");
+
+    if (neighbors_do_private_keys || !flags.hierarchical)
+        e->setPrivateKey();
+    else
+        e->setPublicKey();
+
+    return e;
+}
+
 /* Mark object as expired */
 void
 StoreEntry::expireNow()
 {
     debugs(20, 3, "StoreEntry::expireNow: '" << getMD5Text() << "'");
     expires = squid_curtime;
 }
 
 void
-storeWriteComplete (void *data, StoreIOBuffer wroteBuffer)
-{
-    PROF_start(storeWriteComplete);
-    StoreEntry *e = (StoreEntry *)data;
-
-    if (EBIT_TEST(e->flags, DELAY_SENDING)) {
-        PROF_stop(storeWriteComplete);
-        return;
-    }
-
-    e->invokeHandlers();
-    PROF_stop(storeWriteComplete);
-}
-
-void
 StoreEntry::write (StoreIOBuffer writeBuffer)
 {
     assert(mem_obj != NULL);
     /* This assert will change when we teach the store to update */
     PROF_start(StoreEntry_write);
     assert(store_status == STORE_PENDING);
 
+    // XXX: caller uses content offset, but we also store headers
+    if (const HttpReply *reply = mem_obj->getReply())
+        writeBuffer.offset += reply->hdr_sz;
+
     debugs(20, 5, "storeWrite: writing " << writeBuffer.length << " bytes for '" << getMD5Text() << "'");
     PROF_stop(StoreEntry_write);
     storeGetMemSpace(writeBuffer.length);
-    mem_obj->write (writeBuffer, storeWriteComplete, this);
+    mem_obj->write(writeBuffer);
+
+    if (!EBIT_TEST(flags, DELAY_SENDING))
+        invokeHandlers();
 }
 
 /* Append incoming data from a primary server to an entry. */
 void
 StoreEntry::append(char const *buf, int len)
 {
