void
StoreEntry::adjustVary()
{
    assert(mem_obj);

    if (!mem_obj->request)
        return;

    HttpRequest *request = mem_obj->request;

    if (mem_obj->vary_headers.isEmpty()) {
        /* First handle the case where the object no longer varies */
        request->vary_headers.clear();
    } else {
        if (!request->vary_headers.isEmpty() && request->vary_headers.cmp(mem_obj->vary_headers) != 0) {
            /* Oops.. the variance has changed. Kill the base object
             * to record the new variance key
             */
            request->vary_headers.clear();       /* free old "bad" variance key */
            if (StoreEntry *pe = storeGetPublic(mem_obj->storeId(), mem_obj->method))
                pe->release();
        }

        /* Make sure the request knows the variance status */
        if (request->vary_headers.isEmpty())
            request->vary_headers = httpMakeVaryMark(request, mem_obj->getReply());
    }

    // TODO: storeGetPublic() calls below may create unlocked entries.
    // We should add/use storeHas() API or lock/unlock those entries.
    if (!mem_obj->vary_headers.isEmpty() && !storeGetPublic(mem_obj->storeId(), mem_obj->method)) {
        /* Create "vary" base object */
        String vary;
        StoreEntry *pe = storeCreateEntry(mem_obj->storeId(), mem_obj->logUri(), request->flags, request->method);
        /* We are allowed to do this typecast */
        HttpReply *rep = new HttpReply;
        rep->setHeaders(Http::scOkay, "Internal marker object", "x-squid-internal/vary", -1, -1, squid_curtime + 100000);
        vary = mem_obj->getReply()->header.getList(Http::HdrType::VARY);

        if (vary.size()) {
            /* Again, we own this structure layout */
            rep->header.putStr(Http::HdrType::VARY, vary.termedBuf());
            vary.clean();
        }

#if X_ACCELERATOR_VARY
        vary = mem_obj->getReply()->header.getList(Http::HdrType::HDR_X_ACCELERATOR_VARY);

        if (vary.size() > 0) {
            /* Again, we own this structure layout */
            rep->header.putStr(Http::HdrType::HDR_X_ACCELERATOR_VARY, vary.termedBuf());
            vary.clean();
        }

#endif
        pe->replaceHttpReply(rep, false); // no write until key is public

        pe->timestampsSet();

        pe->makePublic();

        pe->startWriting(); // after makePublic()

        pe->complete();

        pe->unlock("StoreEntry::forcePublicKey+Vary");
    }
}