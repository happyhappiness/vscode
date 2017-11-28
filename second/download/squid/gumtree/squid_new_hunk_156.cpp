
    if (xerrno) {
        str.Printf("Err: (%d) %s\r\n", xerrno, strerror(xerrno));
    } else {
        str.Printf("Err: [none]\r\n");
    }
#if USE_AUTH
    if (auth_user_request->denyMessage())
        str.Printf("Auth ErrMsg: %s\r\n", auth_user_request->denyMessage());
#endif
    if (dnsError.size() > 0)
        str.Printf("DNS ErrMsg: %s\r\n", dnsError.termedBuf());

    /* - TimeStamp */
    str.Printf("TimeStamp: %s\r\n\r\n", mkrfc1123(squid_curtime));

