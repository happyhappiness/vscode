void
netdbExchangeStart(void *data)
{
#if USE_ICMP
    CachePeer *p = (CachePeer *)data;
    char *uri;
    netdbExchangeState *ex;
    StoreIOBuffer tempBuffer;
    CBDATA_INIT_TYPE(netdbExchangeState);
    ex = cbdataAlloc(netdbExchangeState);
    ex->p = cbdataReference(p);
    uri = internalRemoteUri(p->host, p->http_port, "/squid-internal-dynamic/", "netdb");
    debugs(38, 3, "netdbExchangeStart: Requesting '" << uri << "'");
    assert(NULL != uri);
    ex->r = HttpRequest::CreateFromUrl(uri);

    if (NULL == ex->r) {
        debugs(38, DBG_IMPORTANT, "netdbExchangeStart: Bad URI " << uri);
        return;
    }

    HTTPMSGLOCK(ex->r);
    assert(NULL != ex->r);
    ex->r->http_ver = Http::ProtocolVersion(1,1);
    ex->connstate = STATE_HEADER;
    ex->e = storeCreateEntry(uri, uri, RequestFlags(), Http::METHOD_GET);
    ex->buf_sz = NETDB_REQBUF_SZ;
    assert(NULL != ex->e);
    ex->sc = storeClientListAdd(ex->e, ex);
    tempBuffer.offset = 0;
    tempBuffer.length = ex->buf_sz;
    tempBuffer.data = ex->buf;
    storeClientCopy(ex->sc, ex->e, tempBuffer,
                    netdbExchangeHandleReply, ex);
    ex->r->flags.loopDetected = true;   /* cheat! -- force direct */

    if (p->login)
        xstrncpy(ex->r->login, p->login, MAX_LOGIN_SZ);

    urlCanonical(ex->r);

    FwdState::fwdStart(Comm::ConnectionPointer(), ex->e, ex->r);

#endif
}