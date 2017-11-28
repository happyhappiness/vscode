void
HttpStateData::haveParsedReplyHeaders()
{
    ServerStateData::haveParsedReplyHeaders();

    Ctx ctx = ctx_enter(entry->mem_obj->url);
    HttpReply *rep = finalReply();

    if (rep->sline.status == HTTP_PARTIAL_CONTENT &&
            rep->content_range)
        currentOffset = rep->content_range->spec.offset;

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
        const char *vary = httpMakeVaryMark(orig_request, rep);

        if (!vary) {
            entry->makePrivate();
            if (!fwd->reforwardableStatus(rep->sline.status))
                EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
            goto no_cache;
        }

        entry->mem_obj->vary_headers = xstrdup(vary);
    }

#if WIP_FWD_LOG
    fwdStatus(fwd, s);

#endif
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

#if HTTP_VIOLATIONS
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

    if (!ignoreCacheControl && rep->cache_control) {
        if (EBIT_TEST(rep->cache_control->mask, CC_PROXY_REVALIDATE) ||
                EBIT_TEST(rep->cache_control->mask, CC_MUST_REVALIDATE) ||
                EBIT_TEST(rep->cache_control->mask, CC_S_MAXAGE))
            EBIT_SET(entry->flags, ENTRY_REVALIDATE);
    }

#if HEADERS_LOG
    headersLog(1, 0, request->method, rep);

#endif

    ctx_exit(ctx);
}