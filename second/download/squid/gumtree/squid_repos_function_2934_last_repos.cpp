void
clientReplyContext::buildReplyHeader()
{
    HttpHeader *hdr = &reply->header;
    const bool is_hit = http->logType.isTcpHit();
    HttpRequest *request = http->request;
#if DONT_FILTER_THESE
    /* but you might want to if you run Squid as an HTTP accelerator */
    /* hdr->delById(HDR_ACCEPT_RANGES); */
    hdr->delById(HDR_ETAG);
#endif

    if (is_hit || collapsedRevalidation == crSlave)
        hdr->delById(Http::HdrType::SET_COOKIE);
    // TODO: RFC 2965 : Must honour Cache-Control: no-cache="set-cookie2" and remove header.

    // if there is not configured a peer proxy with login=PASS or login=PASSTHRU option enabled
    // remove the Proxy-Authenticate header
    if ( !request->peer_login || (strcmp(request->peer_login,"PASS") != 0 && strcmp(request->peer_login,"PASSTHRU") != 0)) {
#if USE_ADAPTATION
        // but allow adaptation services to authenticate clients
        // via request satisfaction
        if (!http->requestSatisfactionMode())
#endif
            reply->header.delById(Http::HdrType::PROXY_AUTHENTICATE);
    }

    reply->header.removeHopByHopEntries();

    //    if (request->range)
    //      clientBuildRangeHeader(http, reply);

    /*
     * Add a estimated Age header on cache hits.
     */
    if (is_hit) {
        /*
         * Remove any existing Age header sent by upstream caches
         * (note that the existing header is passed along unmodified
         * on cache misses)
         */
        hdr->delById(Http::HdrType::AGE);
        /*
         * This adds the calculated object age. Note that the details of the
         * age calculation is performed by adjusting the timestamp in
         * StoreEntry::timestampsSet(), not here.
         */
        if (EBIT_TEST(http->storeEntry()->flags, ENTRY_SPECIAL)) {
            hdr->delById(Http::HdrType::DATE);
            hdr->putTime(Http::HdrType::DATE, squid_curtime);
        } else if (http->getConn() && http->getConn()->port->actAsOrigin) {
            // Swap the Date: header to current time if we are simulating an origin
            HttpHeaderEntry *h = hdr->findEntry(Http::HdrType::DATE);
            if (h)
                hdr->putExt("X-Origin-Date", h->value.termedBuf());
            hdr->delById(Http::HdrType::DATE);
            hdr->putTime(Http::HdrType::DATE, squid_curtime);
            h = hdr->findEntry(Http::HdrType::EXPIRES);
            if (h && http->storeEntry()->expires >= 0) {
                hdr->putExt("X-Origin-Expires", h->value.termedBuf());
                hdr->delById(Http::HdrType::EXPIRES);
                hdr->putTime(Http::HdrType::EXPIRES, squid_curtime + http->storeEntry()->expires - http->storeEntry()->timestamp);
            }
            if (http->storeEntry()->timestamp <= squid_curtime) {
                // put X-Cache-Age: instead of Age:
                char age[64];
                snprintf(age, sizeof(age), "%" PRId64, static_cast<int64_t>(squid_curtime - http->storeEntry()->timestamp));
                hdr->putExt("X-Cache-Age", age);
            }
        } else if (http->storeEntry()->timestamp <= squid_curtime) {
            hdr->putInt(Http::HdrType::AGE,
                        squid_curtime - http->storeEntry()->timestamp);
            /* Signal old objects.  NB: rfc 2616 is not clear,
             * by implication, on whether we should do this to all
             * responses, or only cache hits.
             * 14.46 states it ONLY applys for heuristically caclulated
             * freshness values, 13.2.4 doesn't specify the same limitation.
             * We interpret RFC 2616 under the combination.
             */
            /* TODO: if maxage or s-maxage is present, don't do this */

            if (squid_curtime - http->storeEntry()->timestamp >= 86400) {
                char tbuf[512];
                snprintf (tbuf, sizeof(tbuf), "%s %s %s",
                          "113", ThisCache,
                          "This cache hit is still fresh and more than 1 day old");
                hdr->putStr(Http::HdrType::WARNING, tbuf);
            }
        }
    }

    /* RFC 2616: Section 14.18
     *
     * Add a Date: header if missing.
     * We have access to a clock therefore are required to amend any shortcoming in servers.
     *
     * NP: done after Age: to prevent ENTRY_SPECIAL double-handling this header.
     */
    if ( !hdr->has(Http::HdrType::DATE) ) {
        if (!http->storeEntry())
            hdr->putTime(Http::HdrType::DATE, squid_curtime);
        else if (http->storeEntry()->timestamp > 0)
            hdr->putTime(Http::HdrType::DATE, http->storeEntry()->timestamp);
        else {
            debugs(88,DBG_IMPORTANT,"BUG 3279: HTTP reply without Date:");
            /* dump something useful about the problem */
            http->storeEntry()->dump(DBG_IMPORTANT);
        }
    }

    // add Warnings required by RFC 2616 if serving a stale hit
    if (http->request->flags.staleIfHit && http->logType.isTcpHit()) {
        hdr->putWarning(110, "Response is stale");
        if (http->request->flags.needValidation)
            hdr->putWarning(111, "Revalidation failed");
    }

    /* Filter unproxyable authentication types */
    if (http->logType.oldType != LOG_TCP_DENIED &&
            hdr->has(Http::HdrType::WWW_AUTHENTICATE)) {
        HttpHeaderPos pos = HttpHeaderInitPos;
        HttpHeaderEntry *e;

        int connection_auth_blocked = 0;
        while ((e = hdr->getEntry(&pos))) {
            if (e->id == Http::HdrType::WWW_AUTHENTICATE) {
                const char *value = e->value.rawBuf();

                if ((strncasecmp(value, "NTLM", 4) == 0 &&
                        (value[4] == '\0' || value[4] == ' '))
                        ||
                        (strncasecmp(value, "Negotiate", 9) == 0 &&
                         (value[9] == '\0' || value[9] == ' '))
                        ||
                        (strncasecmp(value, "Kerberos", 8) == 0 &&
                         (value[8] == '\0' || value[8] == ' '))) {
                    if (request->flags.connectionAuthDisabled) {
                        hdr->delAt(pos, connection_auth_blocked);
                        continue;
                    }
                    request->flags.mustKeepalive = true;
                    if (!request->flags.accelerated && !request->flags.intercepted) {
                        httpHeaderPutStrf(hdr, Http::HdrType::PROXY_SUPPORT, "Session-Based-Authentication");
                        /*
                          We send "Connection: Proxy-Support" header to mark
                          Proxy-Support as a hop-by-hop header for intermediaries that do not
                          understand the semantics of this header. The RFC should have included
                          this recommendation.
                        */
                        httpHeaderPutStrf(hdr, Http::HdrType::CONNECTION, "Proxy-support");
                    }
                    break;
                }
            }
        }

        if (connection_auth_blocked)
            hdr->refreshMask();
    }

#if USE_AUTH
    /* Handle authentication headers */
    if (http->logType.oldType == LOG_TCP_DENIED &&
            ( reply->sline.status() == Http::scProxyAuthenticationRequired ||
              reply->sline.status() == Http::scUnauthorized)
       ) {
        /* Add authentication header */
        /*! \todo alter errorstate to be accel on|off aware. The 0 on the next line
         * depends on authenticate behaviour: all schemes to date send no extra
         * data on 407/401 responses, and do not check the accel state on 401/407
         * responses
         */
        authenticateFixHeader(reply, request->auth_user_request, request, 0, 1);
    } else if (request->auth_user_request != NULL)
        authenticateFixHeader(reply, request->auth_user_request, request, http->flags.accel, 0);
#endif

    /* Append X-Cache */
    httpHeaderPutStrf(hdr, Http::HdrType::X_CACHE, "%s from %s",
                      is_hit ? "HIT" : "MISS", getMyHostname());

#if USE_CACHE_DIGESTS
    /* Append X-Cache-Lookup: -- temporary hack, to be removed @?@ @?@ */
    httpHeaderPutStrf(hdr, Http::HdrType::X_CACHE_LOOKUP, "%s from %s:%d",
                      lookup_type ? lookup_type : "NONE",
                      getMyHostname(), getMyPort());

#endif

    const bool maySendChunkedReply = !request->multipartRangeRequest() &&
                                     reply->sline.protocol == AnyP::PROTO_HTTP && // response is HTTP
                                     (request->http_ver >= Http::ProtocolVersion(1,1));

    /* Check whether we should send keep-alive */
    if (!Config.onoff.error_pconns && reply->sline.status() >= 400 && !request->flags.mustKeepalive) {
        debugs(33, 3, "clientBuildReplyHeader: Error, don't keep-alive");
        request->flags.proxyKeepalive = false;
    } else if (!Config.onoff.client_pconns && !request->flags.mustKeepalive) {
        debugs(33, 2, "clientBuildReplyHeader: Connection Keep-Alive not requested by admin or client");
        request->flags.proxyKeepalive = false;
    } else if (request->flags.proxyKeepalive && shutting_down) {
        debugs(88, 3, "clientBuildReplyHeader: Shutting down, don't keep-alive.");
        request->flags.proxyKeepalive = false;
    } else if (request->flags.connectionAuth && !reply->keep_alive) {
        debugs(33, 2, "clientBuildReplyHeader: Connection oriented auth but server side non-persistent");
        request->flags.proxyKeepalive = false;
    } else if (reply->bodySize(request->method) < 0 && !maySendChunkedReply) {
        debugs(88, 3, "clientBuildReplyHeader: can't keep-alive, unknown body size" );
        request->flags.proxyKeepalive = false;
    } else if (fdUsageHigh()&& !request->flags.mustKeepalive) {
        debugs(88, 3, "clientBuildReplyHeader: Not many unused FDs, can't keep-alive");
        request->flags.proxyKeepalive = false;
    } else if (request->flags.sslBumped && !reply->persistent()) {
        // We do not really have to close, but we pretend we are a tunnel.
        debugs(88, 3, "clientBuildReplyHeader: bumped reply forces close");
        request->flags.proxyKeepalive = false;
    } else if (request->pinnedConnection() && !reply->persistent()) {
        // The peer wants to close the pinned connection
        debugs(88, 3, "pinned reply forces close");
        request->flags.proxyKeepalive = false;
    } else if (http->getConn()) {
        ConnStateData * conn = http->getConn();
        if (!Comm::IsConnOpen(conn->port->listenConn)) {
            // The listening port closed because of a reconfigure
            debugs(88, 3, "listening port closed");
            request->flags.proxyKeepalive = false;
        }
    }

    // Decide if we send chunked reply
    if (maySendChunkedReply && reply->bodySize(request->method) < 0) {
        debugs(88, 3, "clientBuildReplyHeader: chunked reply");
        request->flags.chunkedReply = true;
        hdr->putStr(Http::HdrType::TRANSFER_ENCODING, "chunked");
    }

    hdr->addVia(reply->sline.version);

    /* Signal keep-alive or close explicitly */
    hdr->putStr(Http::HdrType::CONNECTION, request->flags.proxyKeepalive ? "keep-alive" : "close");

#if ADD_X_REQUEST_URI
    /*
     * Knowing the URI of the request is useful when debugging persistent
     * connections in a client; we cannot guarantee the order of http headers,
     * but X-Request-URI is likely to be the very last header to ease use from a
     * debugger [hdr->entries.count-1].
     */
    hdr->putStr(Http::HdrType::X_REQUEST_URI,
                http->memOjbect()->url ? http->memObject()->url : http->uri);

#endif

    /* Surrogate-Control requires Surrogate-Capability from upstream to pass on */
    if ( hdr->has(Http::HdrType::SURROGATE_CONTROL) ) {
        if (!request->header.has(Http::HdrType::SURROGATE_CAPABILITY)) {
            hdr->delById(Http::HdrType::SURROGATE_CONTROL);
        }
        /* TODO: else case: drop any controls intended specifically for our surrogate ID */
    }

    httpHdrMangleList(hdr, request, http->al, ROR_REPLY);
}