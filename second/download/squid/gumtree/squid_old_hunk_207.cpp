        /** \par Host:
         * Normally Squid rewrites the Host: header.
         * However, there is one case when we don't: If the URL
         * went through our redirector and the admin configured
         * 'redir_rewrites_host' to be off.
         */
        if (orig_request->peer_domain)
            hdr_out->putStr(HDR_HOST, orig_request->peer_domain);
        else if (request->flags.redirected && !Config.onoff.redir_rewrites_host)
            hdr_out->addEntry(e->clone());
        else {
            /* use port# only if not default */

            if (orig_request->port == urlDefaultPort(orig_request->protocol)) {
                hdr_out->putStr(HDR_HOST, orig_request->GetHost());
            } else {
                httpHeaderPutStrf(hdr_out, HDR_HOST, "%s:%d",
                                  orig_request->GetHost(),
                                  (int) orig_request->port);
            }
        }

        break;

    case HDR_IF_MODIFIED_SINCE:
