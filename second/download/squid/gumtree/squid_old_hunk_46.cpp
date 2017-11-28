    buf.Printf("Host: " SQUIDSTRINGPH ":%d\r\n", SQUIDSTRINGPRINT(s.host), s.port);
    buf.Printf("Date: %s\r\n", mkrfc1123(squid_curtime));

    if (!TheConfig.reuse_connections)
        buf.Printf("Connection: close\r\n");

    // we must forward "Proxy-Authenticate" and "Proxy-Authorization"
    // as ICAP headers.
    if (virgin.header->header.has(HDR_PROXY_AUTHENTICATE)) {
        String vh=virgin.header->header.getByName("Proxy-Authenticate");
        buf.Printf("Proxy-Authenticate: " SQUIDSTRINGPH "\r\n",SQUIDSTRINGPRINT(vh));
    }

    if (virgin.header->header.has(HDR_PROXY_AUTHORIZATION)) {
        String vh=virgin.header->header.getByName("Proxy-Authorization");
        buf.Printf("Proxy-Authorization: " SQUIDSTRINGPH "\r\n", SQUIDSTRINGPRINT(vh));
    }

    const HttpRequest *request = &virginRequest();

    // share the cross-transactional database records if needed
    if (Adaptation::Config::masterx_shared_name) {
        Adaptation::History::Pointer ah = request->adaptHistory(true);
        if (ah != NULL) {
            String name, value;
            if (ah->getXxRecord(name, value)) {
                buf.Printf(SQUIDSTRINGPH ": " SQUIDSTRINGPH "\r\n",
                           SQUIDSTRINGPRINT(name), SQUIDSTRINGPRINT(value));
            }
