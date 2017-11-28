        /** \par Host:
         * Normally Squid rewrites the Host: header.
         * However, there is one case when we don't: If the URL
         * went through our redirector and the admin configured
         * 'redir_rewrites_host' to be off.
         */
        if (request->peer_domain)
            hdr_out->putStr(HDR_HOST, request->peer_domain);
        else if (request->flags.redirected && !Config.onoff.redir_rewrites_host)
            hdr_out->addEntry(e->clone());
        else {
            /* use port# only if not default */

            if (request->port == urlDefaultPort(request->protocol)) {
                hdr_out->putStr(HDR_HOST, request->GetHost());
            } else {
                httpHeaderPutStrf(hdr_out, HDR_HOST, "%s:%d",
                                  request->GetHost(),
                                  (int) request->port);
            }
        }

        break;

    case HDR_IF_MODIFIED_SINCE:
