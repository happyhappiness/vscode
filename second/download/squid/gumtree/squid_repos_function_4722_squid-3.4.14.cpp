static void
asnCacheStart(int as)
{
    LOCAL_ARRAY(char, asres, 4096);
    StoreEntry *e;
    ASState *asState;
    asState = cbdataAlloc(ASState);
    asState->dataRead = 0;
    debugs(53, 3, "asnCacheStart: AS " << as);
    snprintf(asres, 4096, "whois://%s/!gAS%d", Config.as_whois_server, as);
    asState->as_number = as;
    asState->request = HttpRequest::CreateFromUrl(asres);
    assert(NULL != asState->request);
    HTTPMSGLOCK(asState->request);

    if ((e = storeGetPublic(asres, Http::METHOD_GET)) == NULL) {
        e = storeCreateEntry(asres, asres, RequestFlags(), Http::METHOD_GET);
        asState->sc = storeClientListAdd(e, asState);
        FwdState::fwdStart(Comm::ConnectionPointer(), e, asState->request);
    } else {

        e->lock();
        asState->sc = storeClientListAdd(e, asState);
    }

    asState->entry = e;
    asState->offset = 0;
    asState->reqofs = 0;
    StoreIOBuffer readBuffer (AS_REQBUF_SZ, asState->offset, asState->reqbuf);
    storeClientCopy(asState->sc,
                    e,
                    readBuffer,
                    asHandleReply,
                    asState);
}