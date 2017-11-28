void
copyOneHeaderFromClientsideRequestToUpstreamRequest(const HttpHeaderEntry *e, const String strConnection, HttpRequest * request, const HttpRequest * orig_request, HttpHeader * hdr_out, const int we_do_ranges, const http_state_flags flags)
{
    debugs(11, 5, "httpBuildRequestHeader: " << e->name << ": " << e->value );

    switch (e->id) {

        /** \par RFC 2616 sect 13.5.1 - Hop-by-Hop headers which Squid should not pass on. */

    case HDR_PROXY_AUTHORIZATION:
        /** \par Proxy-Authorization:
         * Only pass on proxy authentication to peers for which
         * authentication forwarding is explicitly enabled
         */

        if (flags.proxying && orig_request->peer_login &&
                (strcmp(orig_request->peer_login, "PASS") == 0 ||
                 strcmp(orig_request->peer_login, "PROXYPASS") == 0)) {
            hdr_out->addEntry(e->clone());
        }

        break;

        /** \par RFC 2616 sect 13.5.1 - Hop-by-Hop headers which Squid does not pass on. */

    case HDR_CONNECTION:          /** \par Connection: */
    case HDR_TE:                  /** \par TE: */
    case HDR_KEEP_ALIVE:          /** \par Keep-Alive: */
    case HDR_PROXY_AUTHENTICATE:  /** \par Proxy-Authenticate: */
    case HDR_TRAILER:             /** \par Trailer: */
    case HDR_UPGRADE:             /** \par Upgrade: */
    case HDR_TRANSFER_ENCODING:   /** \par Transfer-Encoding: */
        break;


        /** \par OTHER headers I haven't bothered to track down yet. */

    case HDR_AUTHORIZATION:
        /** \par WWW-Authorization:
         * Pass on WWW authentication */

        if (!flags.originpeer) {
            hdr_out->addEntry(e->clone());
        } else {
            /** \note In accelerators, only forward authentication if enabled
             * by login=PASS or login=PROXYPASS
             * (see also below for proxy->server authentication)
             */
            if (orig_request->peer_login &&
                    (strcmp(orig_request->peer_login, "PASS") == 0 ||
                     strcmp(orig_request->peer_login, "PROXYPASS") == 0)) {
                hdr_out->addEntry(e->clone());
            }
        }

        break;

    case HDR_HOST:
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
        /** \par If-Modified-Since:
        * append unless we added our own;
         * \note at most one client's ims header can pass through */

        if (!hdr_out->has(HDR_IF_MODIFIED_SINCE))
            hdr_out->addEntry(e->clone());

        break;

    case HDR_MAX_FORWARDS:
        /** \par Max-Forwards:
         * pass only on TRACE or OPTIONS requests */
        if (orig_request->method == METHOD_TRACE || orig_request->method == METHOD_OPTIONS) {
            const int64_t hops = e->getInt64();

            if (hops > 0)
                hdr_out->putInt64(HDR_MAX_FORWARDS, hops - 1);
        }

        break;

    case HDR_VIA:
        /** \par Via:
         * If Via is disabled then forward any received header as-is.
         * Otherwise leave for explicit updated addition later. */

        if (!Config.onoff.via)
            hdr_out->addEntry(e->clone());

        break;

    case HDR_RANGE:

    case HDR_IF_RANGE:

    case HDR_REQUEST_RANGE:
        /** \par Range:, If-Range:, Request-Range:
         * Only pass if we accept ranges */
        if (!we_do_ranges)
            hdr_out->addEntry(e->clone());

        break;

    case HDR_PROXY_CONNECTION: // SHOULD ignore. But doing so breaks things.
        break;

    case HDR_X_FORWARDED_FOR:

    case HDR_CACHE_CONTROL:
        /** \par X-Forwarded-For:, Cache-Control:
         * handled specially by Squid, so leave off for now.
         * append these after the loop if needed */
        break;

    case HDR_FRONT_END_HTTPS:
        /** \par Front-End-Https:
         * Pass thru only if peer is configured with front-end-https */
        if (!flags.front_end_https)
            hdr_out->addEntry(e->clone());

        break;

    default:
        /** \par default.
         * pass on all other header fields
         * which are NOT listed by the special Connection: header. */

        if (strConnection.size()>0 && strListIsMember(&strConnection, e->name.termedBuf(), ',')) {
            debugs(11, 2, "'" << e->name << "' header cropped by Connection: definition");
            return;
        }

        hdr_out->addEntry(e->clone());
    }
}