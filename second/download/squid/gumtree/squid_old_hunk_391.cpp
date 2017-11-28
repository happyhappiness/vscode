    httpHeaderPutStrf(hdr, HDR_X_CACHE_LOOKUP, "%s from %s:%d",
                      lookup_type ? lookup_type : "NONE",
                      getMyHostname(), getMyPort());

#endif

    // XXX: chunking a Content-Range response may not violate specs, but our
    // ClientSocketContext::writeComplete() confuses the end of ClientStream
    // with the end of to-client writing and may quit before writing last-chunk
    const bool maySendChunkedReply = !reply->content_range &&
                                     !request->multipartRangeRequest() &&
                                     reply->sline.protocol == AnyP::PROTO_HTTP && // response is HTTP
                                     (request->http_ver >= HttpVersion(1, 1));

    /* Check whether we should send keep-alive */
    if (!Config.onoff.error_pconns && reply->sline.status >= 400 && !request->flags.must_keepalive) {
        debugs(33, 3, "clientBuildReplyHeader: Error, don't keep-alive");
        request->flags.proxy_keepalive = 0;
    } else if (!Config.onoff.client_pconns && !request->flags.must_keepalive) {
        debugs(33, 2, "clientBuildReplyHeader: Connection Keep-Alive not requested by admin or client");
        request->flags.proxy_keepalive = 0;
    } else if (request->flags.proxy_keepalive && shutting_down) {
        debugs(88, 3, "clientBuildReplyHeader: Shutting down, don't keep-alive.");
        request->flags.proxy_keepalive = 0;
    } else if (request->flags.connection_auth && !reply->keep_alive) {
        debugs(33, 2, "clientBuildReplyHeader: Connection oriented auth but server side non-persistent");
        request->flags.proxy_keepalive = 0;
    } else if (reply->bodySize(request->method) < 0 && !maySendChunkedReply) {
        debugs(88, 3, "clientBuildReplyHeader: can't keep-alive, unknown body size" );
        request->flags.proxy_keepalive = 0;
    } else if (fdUsageHigh()&& !request->flags.must_keepalive) {
        debugs(88, 3, "clientBuildReplyHeader: Not many unused FDs, can't keep-alive");
        request->flags.proxy_keepalive = 0;
    }

    // Decide if we send chunked reply
    if (maySendChunkedReply &&
            request->flags.proxy_keepalive &&
            reply->bodySize(request->method) < 0) {
        debugs(88, 3, "clientBuildReplyHeader: chunked reply");
        request->flags.chunked_reply = 1;
        hdr->putStr(HDR_TRANSFER_ENCODING, "chunked");
    }

    /* Append VIA */
    if (Config.onoff.via) {
        LOCAL_ARRAY(char, bbuf, MAX_URL + 32);
