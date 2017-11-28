        buf.Printf("res-body=%d", (int) httpBuf.contentSize());

    buf.append(ICAP::crlf, 2); // terminate Encapsulated line

    if (preview.enabled()) {
        buf.Printf("Preview: %d\r\n", (int)preview.ad());
        if (!virginBody.expected()) // there is no body to preview
            finishNullOrEmptyBodyPreview(httpBuf);
    }

    makeAllowHeader(buf);

    if (TheConfig.send_client_ip && request) {
        Ip::Address client_addr;
#if FOLLOW_X_FORWARDED_FOR
        if (TheConfig.use_indirect_client) {
            client_addr = request->indirect_client_addr;
        } else
#endif
            client_addr = request->client_addr;
        if (!client_addr.IsAnyAddr() && !client_addr.IsNoAddr())
            buf.Printf("X-Client-IP: %s\r\n", client_addr.NtoA(ntoabuf,MAX_IPSTRLEN));
    }

    if (TheConfig.send_username && request)
        makeUsernameHeader(request, buf);

    // Adaptation::Config::metaHeaders
    typedef Adaptation::Config::MetaHeaders::iterator ACAMLI;
    for (ACAMLI i = Adaptation::Config::metaHeaders.begin(); i != Adaptation::Config::metaHeaders.end(); ++i) {
        HttpRequest *r = virgin.cause ?
                         virgin.cause : dynamic_cast<HttpRequest*>(virgin.header);
        Must(r);

        HttpReply *reply = dynamic_cast<HttpReply*>(virgin.header);

        if (const char *value = (*i)->match(r, reply))
            buf.Printf("%s: %s\r\n", (*i)->name.termedBuf(), value);
    }

    // fprintf(stderr, "%s\n", buf.content());

    buf.append(ICAP::crlf, 2); // terminate ICAP header

    // fill icapRequest for logging
    Must(icapRequest->parseCharBuf(buf.content(), buf.contentSize()));
