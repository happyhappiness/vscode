{
    char ntoabuf[MAX_IPSTRLEN];
    /*
     * XXX These should use HttpHdr interfaces instead of Printfs
     */
    const Adaptation::ServiceConfig &s = service().cfg();
    buf.Printf("%s " SQUIDSTRINGPH " ICAP/1.0\r\n", s.methodStr(), SQUIDSTRINGPRINT(s.uri));
    buf.Printf("Host: " SQUIDSTRINGPH ":%d\r\n", SQUIDSTRINGPRINT(s.host), s.port);
    buf.Printf("Date: %s\r\n", mkrfc1123(squid_curtime));

    if (!TheConfig.reuse_connections)
        buf.Printf("Connection: close\r\n");

    const HttpRequest *request = &virginRequest();

    // we must forward "Proxy-Authenticate" and "Proxy-Authorization"
    // as ICAP headers.
    if (virgin.header->header.has(HDR_PROXY_AUTHENTICATE)) {
        String vh=virgin.header->header.getByName("Proxy-Authenticate");
        buf.Printf("Proxy-Authenticate: " SQUIDSTRINGPH "\r\n",SQUIDSTRINGPRINT(vh));
    }

    if (virgin.header->header.has(HDR_PROXY_AUTHORIZATION)) {
        String vh=virgin.header->header.getByName("Proxy-Authorization");
        buf.Printf("Proxy-Authorization: " SQUIDSTRINGPH "\r\n", SQUIDSTRINGPRINT(vh));
    } else if (request->extacl_user.size() > 0 && request->extacl_passwd.size() > 0) {
        char loginbuf[256];
        snprintf(loginbuf, sizeof(loginbuf), SQUIDSTRINGPH ":" SQUIDSTRINGPH,
                 SQUIDSTRINGPRINT(request->extacl_user),
                 SQUIDSTRINGPRINT(request->extacl_passwd));
        buf.Printf("Proxy-Authorization: Basic %s\r\n", old_base64_encode(loginbuf));
    }

    // share the cross-transactional database records if needed
    if (Adaptation::Config::masterx_shared_name) {
        Adaptation::History::Pointer ah = request->adaptHistory(false);
        if (ah != NULL) {
            String name, value;
            if (ah->getXxRecord(name, value)) {
                buf.Printf(SQUIDSTRINGPH ": " SQUIDSTRINGPH "\r\n",
                           SQUIDSTRINGPRINT(name), SQUIDSTRINGPRINT(value));
            }
        }
    }

    buf.Printf("Encapsulated: ");

    MemBuf httpBuf;

    httpBuf.init();

    // build HTTP request header, if any
    ICAP::Method m = s.method;

    // to simplify, we could assume that request is always available

    String urlPath;
    if (request) {
        urlPath = request->urlpath;
        if (ICAP::methodRespmod == m)
            encapsulateHead(buf, "req-hdr", httpBuf, request);
        else if (ICAP::methodReqmod == m)
            encapsulateHead(buf, "req-hdr", httpBuf, virgin.header);
    }

    if (ICAP::methodRespmod == m)
        if (const HttpMsg *prime = virgin.header)
            encapsulateHead(buf, "res-hdr", httpBuf, prime);

    if (!virginBody.expected())
        buf.Printf("null-body=%d", (int) httpBuf.contentSize());
    else if (ICAP::methodReqmod == m)
        buf.Printf("req-body=%d", (int) httpBuf.contentSize());
    else
        buf.Printf("res-body=%d", (int) httpBuf.contentSize());

    buf.append(ICAP::crlf, 2); // terminate Encapsulated line

    if (preview.enabled()) {
        buf.Printf("Preview: %d\r\n", (int)preview.ad());
        if (!virginBody.expected()) // there is no body to preview
            finishNullOrEmptyBodyPreview(httpBuf);
    }

    makeAllowHeader(buf);

