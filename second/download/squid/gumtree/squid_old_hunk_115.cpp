    httpHeaderPutStrf(hdr, HDR_X_CACHE_LOOKUP, "%s from %s:%d",
                      lookup_type ? lookup_type : "NONE",
                      getMyHostname(), getMyPort());

#endif

    /* Check whether we should send keep-alive */
    if (!Config.onoff.error_pconns && reply->sline.status >= 400 && !request->flags.must_keepalive) {
        debugs(33, 3, "clientBuildReplyHeader: Error, don't keep-alive");
        request->flags.proxy_keepalive = 0;
    } else if (!Config.onoff.client_pconns && !request->flags.must_keepalive) {
        debugs(33, 2, "clientBuildReplyHeader: Connection Keep-Alive not requested by admin or client");
