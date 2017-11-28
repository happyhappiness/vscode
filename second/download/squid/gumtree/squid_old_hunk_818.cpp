    /** If set to DELETE - do not copy through. */

    /* append Host if not there already */
    if (!hdr_out->has(HDR_HOST)) {
        if (request->peer_domain) {
            hdr_out->putStr(HDR_HOST, request->peer_domain);
        } else if (request->port == urlDefaultPort(request->protocol)) {
            /* use port# only if not default */
            hdr_out->putStr(HDR_HOST, request->GetHost());
        } else {
            httpHeaderPutStrf(hdr_out, HDR_HOST, "%s:%d",
                              request->GetHost(),
                              (int) request->port);
