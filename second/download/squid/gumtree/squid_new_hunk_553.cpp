    if (xerrno) {
        str.Printf("Err: (%d) %s\r\n", xerrno, strerror(xerrno));
    } else {
        str.Printf("Err: [none]\r\n");
    }
#if USE_AUTH
    if (auth_user_request.getRaw() && auth_user_request->denyMessage())
        str.Printf("Auth ErrMsg: %s\r\n", auth_user_request->denyMessage());
#endif
    if (dnsError.size() > 0)
        str.Printf("DNS ErrMsg: %s\r\n", dnsError.termedBuf());

    /* - TimeStamp */
    str.Printf("TimeStamp: %s\r\n\r\n", mkrfc1123(squid_curtime));

    /* - IP stuff */
    str.Printf("ClientIP: %s\r\n", src_addr.toStr(ntoabuf,MAX_IPSTRLEN));

    if (request && request->hier.host[0] != '\0') {
        str.Printf("ServerIP: %s\r\n", request->hier.host);
    }

    str.Printf("\r\n");
