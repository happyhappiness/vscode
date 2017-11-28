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

    fetch->request = HTTPMSGLOCK(req);
