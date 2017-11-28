    storeAppendPrintf(s, "NETDB support not compiled into this Squid cache.\n");
#endif

    s->complete();
}

void
netdbExchangeStart(void *data)
{
#if USE_ICMP
    CachePeer *p = (CachePeer *)data;
    static const SBuf netDB("netdb");
    char *uri = internalRemoteUri(p->host, p->http_port, "/squid-internal-dynamic/", netDB);
    debugs(38, 3, "netdbExchangeStart: Requesting '" << uri << "'");
    assert(NULL != uri);
    HttpRequest *req = HttpRequest::CreateFromUrl(uri);

    if (req == NULL) {
        debugs(38, DBG_IMPORTANT, "netdbExchangeStart: Bad URI " << uri);
        return;
    }

    netdbExchangeState *ex = new netdbExchangeState(p, req);
    ex->e = storeCreateEntry(uri, uri, RequestFlags(), Http::METHOD_GET);
    assert(NULL != ex->e);

    StoreIOBuffer tempBuffer;
    tempBuffer.length = ex->buf_sz;
    tempBuffer.data = ex->buf;

    ex->sc = storeClientListAdd(ex->e, ex);

    storeClientCopy(ex->sc, ex->e, tempBuffer,
                    netdbExchangeHandleReply, ex);
    ex->r->flags.loopDetected = true;   /* cheat! -- force direct */

    // XXX: send as Proxy-Authenticate instead
    if (p->login)
        ex->r->url.userInfo(SBuf(p->login));

    FwdState::fwdStart(Comm::ConnectionPointer(), ex->e, ex->r);

#endif
}

