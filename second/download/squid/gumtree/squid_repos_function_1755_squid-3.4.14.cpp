static void
peerDigestRequest(PeerDigest * pd)
{
    CachePeer *p = pd->peer;
    StoreEntry *e, *old_e;
    char *url = NULL;
    const cache_key *key;
    HttpRequest *req;
    DigestFetchState *fetch = NULL;
    StoreIOBuffer tempBuffer;

    pd->req_result = NULL;
    pd->flags.requested = true;

    /* compute future request components */

    if (p->digest_url)
        url = xstrdup(p->digest_url);
    else
        url = xstrdup(internalRemoteUri(p->host, p->http_port, "/squid-internal-periodic/", StoreDigestFileName));

    req = HttpRequest::CreateFromUrl(url);

    assert(req);

    key = storeKeyPublicByRequest(req);

    debugs(72, 2, "peerDigestRequest: " << url << " key: " << storeKeyText(key));

    /* add custom headers */
    assert(!req->header.len);

    req->header.putStr(HDR_ACCEPT, StoreDigestMimeStr);

    req->header.putStr(HDR_ACCEPT, "text/html");

    if (p->login &&
            p->login[0] != '*' &&
            strcmp(p->login, "PASS") != 0 &&
            strcmp(p->login, "PASSTHRU") != 0 &&
            strcmp(p->login, "NEGOTIATE") != 0 &&
            strcmp(p->login, "PROXYPASS") != 0) {
        xstrncpy(req->login, p->login, MAX_LOGIN_SZ);
    }
    /* create fetch state structure */
    CBDATA_INIT_TYPE(DigestFetchState);

    fetch = cbdataAlloc(DigestFetchState);

    fetch->request = req;
    HTTPMSGLOCK(fetch->request);

    fetch->pd = cbdataReference(pd);

    fetch->offset = 0;

    fetch->state = DIGEST_READ_REPLY;

    /* update timestamps */
    fetch->start_time = squid_curtime;

    pd->times.requested = squid_curtime;

    pd_last_req_time = squid_curtime;

    req->flags.cachable = true;

    /* the rest is based on clientProcessExpired() */
    req->flags.refresh = true;

    old_e = fetch->old_entry = Store::Root().get(key);

    if (old_e) {
        debugs(72, 5, "peerDigestRequest: found old entry");

        old_e->lock();
        old_e->createMemObject(url, url);

        fetch->old_sc = storeClientListAdd(old_e, fetch);
    }

    e = fetch->entry = storeCreateEntry(url, url, req->flags, req->method);
    assert(EBIT_TEST(e->flags, KEY_PRIVATE));
    fetch->sc = storeClientListAdd(e, fetch);
    /* set lastmod to trigger IMS request if possible */

    if (old_e)
        e->lastmod = old_e->lastmod;

    /* push towards peer cache */
    debugs(72, 3, "peerDigestRequest: forwarding to fwdStart...");

    FwdState::fwdStart(Comm::ConnectionPointer(), e, req);

    tempBuffer.offset = 0;

    tempBuffer.length = SM_PAGE_SIZE;

    tempBuffer.data = fetch->buf;

    storeClientCopy(fetch->sc, e, tempBuffer,
                    peerDigestHandleReply, fetch);

    safe_free(url);
}