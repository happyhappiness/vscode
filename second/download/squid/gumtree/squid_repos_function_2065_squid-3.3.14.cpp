void
HttpStateData::haveParsedReplyHeaders()
{
    ServerStateData::haveParsedReplyHeaders();

    Ctx ctx = ctx_enter(entry->mem_obj->url);
    HttpReply *rep = finalReply();

    entry->timestampsSet();

    /* Check if object is cacheable or not based on reply code */
    debugs(11, 3, "haveParsedReplyHeaders: HTTP CODE: " << rep->sline.status);

    if (neighbors_do_private_keys)
        httpMaybeRemovePublic(entry, rep->sline.status);

    if (rep->header.has(HDR_VARY)
#if X_ACCELERATOR_VARY
            || rep->header.has(HDR_X_ACCELERATOR_VARY)
#endif
       ) {
        const char *vary = httpMakeVaryMark(request, rep);

        if (!vary) {
            entry->makePrivate();
            if (!fwd->reforwardableStatus(rep->sline.status))
                EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
            goto no_cache;
        }

        entry->mem_obj->vary_headers = xstrdup(vary);
    }

    /*
     * If its not a reply that we will re-forward, then
     * allow the client to get it.
     */
    if (!fwd->reforwardableStatus(rep->sline.status))
        EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);

    switch (cacheableReply()) {

    case 1:
        entry->makePublic();
        break;

    case 0:
        entry->makePrivate();
        break;

    case -1:

#if USE_HTTP_VIOLATIONS
        if (Config.negativeTtl > 0)
            entry->cacheNegatively();
        else
#endif
            entry->makePrivate();

        break;

    default:
        assert(0);

        break;
    }

no_cache:

    if (!ignoreCacheControl) {
        if (rep->cache_control) {
            // We are required to revalidate on many conditions.
            // For security reasons we do so even if storage was caused by refresh_pattern ignore-* option

            // CC:must-revalidate or CC:proxy-revalidate
            const bool ccMustRevalidate = (rep->cache_control->proxyRevalidate() || rep->cache_control->mustRevalidate());

            // CC:no-cache (only if there are no parameters)
            const bool ccNoCacheNoParams = (rep->cache_control->hasNoCache() && rep->cache_control->noCache().undefined());

            // CC:s-maxage=N
            const bool ccSMaxAge = rep->cache_control->hasSMaxAge();

            // CC:private (yes, these can sometimes be stored)
            const bool ccPrivate = rep->cache_control->hasPrivate();

            if (ccMustRevalidate || ccNoCacheNoParams || ccSMaxAge || ccPrivate)
                EBIT_SET(entry->flags, ENTRY_REVALIDATE);
        }
#if USE_HTTP_VIOLATIONS // response header Pragma::no-cache is undefined in HTTP
        else {
            // Expensive calculation. So only do it IF the CC: header is not present.

            /* HACK: Pragma: no-cache in _replies_ is not documented in HTTP,
             * but servers like "Active Imaging Webcast/2.0" sure do use it */
            if (rep->header.has(HDR_PRAGMA) &&
                    rep->header.hasListMember(HDR_PRAGMA,"no-cache",','))
                EBIT_SET(entry->flags, ENTRY_REVALIDATE);
        }
#endif
    }

#if HEADERS_LOG
    headersLog(1, 0, request->method, rep);

#endif

    ctx_exit(ctx);
}