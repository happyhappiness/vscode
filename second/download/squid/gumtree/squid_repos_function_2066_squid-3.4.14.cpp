static void
httpMaybeRemovePublic(StoreEntry * e, Http::StatusCode status)
{
    int remove = 0;
    int forbidden = 0;
    StoreEntry *pe;

    if (!EBIT_TEST(e->flags, KEY_PRIVATE))
        return;

    switch (status) {

    case Http::scOkay:

    case Http::scNonAuthoritativeInformation:

    case Http::scMultipleChoices:

    case Http::scMovedPermanently:

    case Http::scFound:

    case Http::scGone:

    case Http::scNotFound:
        remove = 1;

        break;

    case Http::scForbidden:

    case Http::scMethodNotAllowed:
        forbidden = 1;

        break;

#if WORK_IN_PROGRESS

    case Http::scUnauthorized:
        forbidden = 1;

        break;

#endif

    default:
#if QUESTIONABLE
        /*
         * Any 2xx response should eject previously cached entities...
         */

        if (status >= 200 && status < 300)
            remove = 1;

#endif

        break;
    }

    if (!remove && !forbidden)
        return;

    assert(e->mem_obj);

    if (e->mem_obj->request)
        pe = storeGetPublicByRequest(e->mem_obj->request);
    else
        pe = storeGetPublic(e->mem_obj->url, e->mem_obj->method);

    if (pe != NULL) {
        assert(e != pe);
#if USE_HTCP
        neighborsHtcpClear(e, NULL, e->mem_obj->request, e->mem_obj->method, HTCP_CLR_INVALIDATION);
#endif
        pe->release();
    }

    /** \par
     * Also remove any cached HEAD response in case the object has
     * changed.
     */
    if (e->mem_obj->request)
        pe = storeGetPublicByRequestMethod(e->mem_obj->request, Http::METHOD_HEAD);
    else
        pe = storeGetPublic(e->mem_obj->url, Http::METHOD_HEAD);

    if (pe != NULL) {
        assert(e != pe);
#if USE_HTCP
        neighborsHtcpClear(e, NULL, e->mem_obj->request, HttpRequestMethod(Http::METHOD_HEAD), HTCP_CLR_INVALIDATION);
#endif
        pe->release();
    }
}