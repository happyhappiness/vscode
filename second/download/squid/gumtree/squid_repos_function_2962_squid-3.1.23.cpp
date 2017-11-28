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
        debugs(20, 1, "assertion failed: RELEASE key " << key << ", url " << mem_obj->url);

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

        if (mem_obj->vary_headers && !storeGetPublic(mem_obj->url, mem_obj->method)) {
            /* Create "vary" base object */
            String vary;
            StoreEntry *pe = storeCreateEntry(mem_obj->url, mem_obj->log_url, request->flags, request->method);
            /* We are allowed to do this typecast */
            HttpReply *rep = new HttpReply;
            rep->setHeaders(HTTP_OK, "Internal marker object", "x-squid-internal/vary", -1, -1, squid_curtime + 100000);
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
            pe->replaceHttpReply(rep);

            pe->timestampsSet();

            pe->makePublic();

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