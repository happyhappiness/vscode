            hdr_out->putStr(HDR_HOST, request->peer_domain);
        else if (request->flags.redirected && !Config.onoff.redir_rewrites_host)
            hdr_out->addEntry(e->clone());
        else {
            /* use port# only if not default */

            if (request->port == urlDefaultPort(request->url.getScheme())) {
                hdr_out->putStr(HDR_HOST, request->GetHost());
            } else {
                httpHeaderPutStrf(hdr_out, HDR_HOST, "%s:%d",
                                  request->GetHost(),
                                  (int) request->port);
            }
