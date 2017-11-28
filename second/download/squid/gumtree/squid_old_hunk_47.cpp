        buf.Printf("res-body=%d", (int) httpBuf.contentSize());

    buf.append(ICAP::crlf, 2); // terminate Encapsulated line

    if (preview.enabled()) {
        buf.Printf("Preview: %d\r\n", (int)preview.ad());
        if (virginBody.expected()) // there is a body to preview
            virginBodySending.plan();
        else
            finishNullOrEmptyBodyPreview(httpBuf);
    }

    if (shouldAllow204()) {
        debugs(93,5, HERE << "will allow 204s outside of preview");
        state.allowedPostview204 = true;
        buf.Printf("Allow: 204\r\n");
        if (virginBody.expected()) // there is a body to echo
            virginBodySending.plan();
    }

    if (TheConfig.send_client_ip && request) {
        IpAddress client_addr;
#if FOLLOW_X_FORWARDED_FOR
        if (TheConfig.icap_uses_indirect_client) {
            client_addr = request->indirect_client_addr;
        } else
#endif
            client_addr = request->client_addr;
        if (!client_addr.IsAnyAddr() && !client_addr.IsNoAddr())
            buf.Printf("X-Client-IP: %s\r\n", client_addr.NtoA(ntoabuf,MAX_IPSTRLEN));
    }

    if (TheConfig.send_client_username && request)
        makeUsernameHeader(request, buf);

    // fprintf(stderr, "%s\n", buf.content());

    buf.append(ICAP::crlf, 2); // terminate ICAP header

    // fill icapRequest for logging
    Must(icapRequest->parseCharBuf(buf.content(), buf.contentSize()));
