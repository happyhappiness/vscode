    assert(!req->header.len);

    req->header.putStr(HDR_ACCEPT, StoreDigestMimeStr);

    req->header.putStr(HDR_ACCEPT, "text/html");

    if (p->login)
        xstrncpy(req->login, p->login, MAX_LOGIN_SZ);

    /* create fetch state structure */
    CBDATA_INIT_TYPE(DigestFetchState);

    fetch = cbdataAlloc(DigestFetchState);

    fetch->request = HTTPMSGLOCK(req);
