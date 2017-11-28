    } else if (request->flags.proxy_keepalive && shutting_down) {
        debugs(88, 3, "clientBuildReplyHeader: Shutting down, don't keep-alive.");
        request->flags.proxy_keepalive = 0;
    } else if (request->flags.connection_auth && !reply->keep_alive) {
        debugs(33, 2, "clientBuildReplyHeader: Connection oriented auth but server side non-persistent");
        request->flags.proxy_keepalive = 0;
    } else if (reply->bodySize(request->method) < 0) {
        debugs(88, 3, "clientBuildReplyHeader: can't keep-alive, unknown body size" );
        request->flags.proxy_keepalive = 0;
    } else if (fdUsageHigh()&& !request->flags.must_keepalive) {
        debugs(88, 3, "clientBuildReplyHeader: Not many unused FDs, can't keep-alive");
        request->flags.proxy_keepalive = 0;
    }

    /* Append VIA */
    if (Config.onoff.via) {
        LOCAL_ARRAY(char, bbuf, MAX_URL + 32);
        String strVia;
        hdr->getList(HDR_VIA, &strVia);
        snprintf(bbuf, MAX_URL + 32, "%d.%d %s",
