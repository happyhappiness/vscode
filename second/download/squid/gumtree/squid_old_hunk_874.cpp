    const cache_key *newkey;

    if (key && EBIT_TEST(flags, KEY_PRIVATE))
        return;                 /* is already private */

    if (key) {
        if (swap_filen > -1)
            storeDirSwapLog(this, SWAP_LOG_DEL);

        hashDelete();
    }

    if (mem_obj != NULL) {
        mem_obj->id = getKeyCounter();
        newkey = storeKeyPrivate(mem_obj->url, mem_obj->method, mem_obj->id);
    } else {
        newkey = storeKeyPrivate("JUNK", Http::METHOD_NONE, getKeyCounter());
    }

    assert(hash_lookup(store_table, newkey) == NULL);
    EBIT_SET(flags, KEY_PRIVATE);
    hashInsert(newkey);
}

void
StoreEntry::setPublicKey()
{
    StoreEntry *e2 = NULL;
    const cache_key *newkey;

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
     * If RELEASE_REQUEST is set, then ENTRY_CACHABLE should not
     * be set, and StoreEntry::setPublicKey() should not be called.
     */
#if MORE_DEBUG_OUTPUT

    if (EBIT_TEST(flags, RELEASE_REQUEST))
        debugs(20, DBG_IMPORTANT, "assertion failed: RELEASE key " << key << ", url " << mem_obj->url);

#endif

    assert(!EBIT_TEST(flags, RELEASE_REQUEST));

    if (mem_obj->request) {
        HttpRequest *request = mem_obj->request;

        if (!mem_obj->vary_headers) {
            /* First handle the case where the object no longer varies */
            safe_free(request->vary_headers);
        } else {
            if (request->vary_headers && strcmp(request->vary_headers, mem_obj->vary_headers) != 0) {
                /* Oops.. the variance has changed. Kill the base object
                 * to record the new variance key
                 */
                safe_free(request->vary_headers);       /* free old "bad" variance key */
                StoreEntry *pe = storeGetPublic(mem_obj->url, mem_obj->method);

                if (pe)
                    pe->release();
            }

            /* Make sure the request knows the variance status */
            if (!request->vary_headers) {
                const char *vary = httpMakeVaryMark(request, mem_obj->getReply());

                if (vary)
                    request->vary_headers = xstrdup(vary);
            }
        }

        // TODO: storeGetPublic() calls below may create unlocked entries.
        // We should add/use storeHas() API or lock/unlock those entries.
        if (mem_obj->vary_headers && !storeGetPublic(mem_obj->url, mem_obj->method)) {
            /* Create "vary" base object */
            String vary;
            StoreEntry *pe = storeCreateEntry(mem_obj->url, mem_obj->log_url, request->flags, request->method);
            /* We are allowed to do this typecast */
            HttpReply *rep = new HttpReply;
            rep->setHeaders(Http::scOkay, "Internal marker object", "x-squid-internal/vary", -1, -1, squid_curtime + 100000);
            vary = mem_obj->getReply()->header.getList(HDR_VARY);

            if (vary.size()) {
                /* Again, we own this structure layout */
                rep->header.putStr(HDR_VARY, vary.termedBuf());
                vary.clean();
            }

#if X_ACCELERATOR_VARY
            vary = mem_obj->getReply()->header.getList(HDR_X_ACCELERATOR_VARY);

            if (vary.defined()) {
                /* Again, we own this structure layout */
                rep->header.putStr(HDR_X_ACCELERATOR_VARY, vary.termedBuf());
                vary.clean();
            }

#endif
            pe->replaceHttpReply(rep, false); // no write until key is public

            pe->timestampsSet();

            pe->makePublic();

            pe->startWriting(); // after makePublic()

            pe->complete();

            pe->unlock();
        }

        newkey = storeKeyPublicByRequest(mem_obj->request);
    } else
        newkey = storeKeyPublic(mem_obj->url, mem_obj->method);

    if ((e2 = (StoreEntry *) hash_lookup(store_table, newkey))) {
        debugs(20, 3, "StoreEntry::setPublicKey: Making old '" << mem_obj->url << "' private.");
        e2->setPrivateKey();
        e2->release();

        if (mem_obj->request)
            newkey = storeKeyPublicByRequest(mem_obj->request);
        else
            newkey = storeKeyPublic(mem_obj->url, mem_obj->method);
    }

    if (key)
        hashDelete();

    EBIT_CLR(flags, KEY_PRIVATE);

    hashInsert(newkey);

    if (swap_filen > -1)
        storeDirSwapLog(this, SWAP_LOG_ADD);
}

StoreEntry *
storeCreateEntry(const char *url, const char *log_url, const RequestFlags &flags, const HttpRequestMethod& method)
{
    StoreEntry *e = NULL;
    MemObject *mem = NULL;
    debugs(20, 3, "storeCreateEntry: '" << url << "'");

    e = new StoreEntry(url, log_url);
    e->lock_count = 1;          /* Note lock here w/o calling storeLock() */
    mem = e->mem_obj;
    mem->method = method;

    if (neighbors_do_private_keys || !flags.hierarchical)
        e->setPrivateKey();
    else
        e->setPublicKey();

    if (flags.cachable) {
        EBIT_SET(e->flags, ENTRY_CACHABLE);
        EBIT_CLR(e->flags, RELEASE_REQUEST);
    } else {
        /* StoreEntry::releaseRequest() clears ENTRY_CACHABLE */
        e->releaseRequest();
    }

    e->store_status = STORE_PENDING;
    e->setMemStatus(NOT_IN_MEMORY);
    e->refcount = 0;
    e->lastref = squid_curtime;
    e->timestamp = -1;          /* set in StoreEntry::timestampsSet() */
    e->ping_status = PING_NONE;
    EBIT_SET(e->flags, ENTRY_VALIDATED);
    return e;
}

/* Mark object as expired */
void
StoreEntry::expireNow()
{
    debugs(20, 3, "StoreEntry::expireNow: '" << getMD5Text() << "'");
    expires = squid_curtime;
}

void
storeWriteComplete (void *data, StoreIOBuffer wroteBuffer)
{
    PROF_start(storeWriteComplete);
    StoreEntry *e = (StoreEntry *)data;

    if (EBIT_TEST(e->flags, DELAY_SENDING)) {
        PROF_stop(storeWriteComplete);
        return;
    }

    e->invokeHandlers();
    PROF_stop(storeWriteComplete);
}

void
StoreEntry::write (StoreIOBuffer writeBuffer)
{
    assert(mem_obj != NULL);
    /* This assert will change when we teach the store to update */
    PROF_start(StoreEntry_write);
    assert(store_status == STORE_PENDING);

    debugs(20, 5, "storeWrite: writing " << writeBuffer.length << " bytes for '" << getMD5Text() << "'");
    PROF_stop(StoreEntry_write);
    storeGetMemSpace(writeBuffer.length);
    mem_obj->write (writeBuffer, storeWriteComplete, this);
}

/* Append incoming data from a primary server to an entry. */
void
StoreEntry::append(char const *buf, int len)
{
