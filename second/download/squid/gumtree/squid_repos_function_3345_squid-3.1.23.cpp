void
clientReplyContext::buildReplyHeader()
{
    HttpHeader *hdr = &reply->header;
    int is_hit = logTypeIsATcpHit(http->logType);
    HttpRequest *request = http->request;
#if DONT_FILTER_THESE
    /* but you might want to if you run Squid as an HTTP accelerator */
    /* hdr->delById(HDR_ACCEPT_RANGES); */
    hdr->delById(HDR_ETAG);
#endif

    if (is_hit)
        hdr->delById(HDR_SET_COOKIE);
    // TODO: RFC 2965 : Must honour Cache-Control: no-cache="set-cookie2" and remove header.

    // if there is not configured a peer proxy with login=PASS option enabled
    // remove the Proxy-Authenticate header
    if ( !(request->peer_login && strcmp(request->peer_login,"PASS") ==0))
        reply->header.delById(HDR_PROXY_AUTHENTICATE);

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
        hdr->delById(HDR_AGE);
        /*
         * This adds the calculated object age. Note that the details of the
         * age calculation is performed by adjusting the timestamp in
         * StoreEntry::timestampsSet(), not here.
         *
         * BROWSER WORKAROUND: IE sometimes hangs when receiving a 0 Age
         * header, so don't use it unless there is a age to report. Please
         * note that Age is only used to make a conservative estimation of
         * the objects age, so a Age: 0 header does not add any useful
         * information to the reply in any case.
         */
#if DEAD_CODE
        // XXX: realy useless? or is there a bug now that this is detatched from the below if-sequence ?
        // looks like this pre-if was supposed to be the browser workaround...
        if (NULL == http->storeEntry())
            (void) 0;
        else if (http->storeEntry()->timestamp < 0)
            (void) 0;
#endif

        if (EBIT_TEST(http->storeEntry()->flags, ENTRY_SPECIAL)) {
            hdr->delById(HDR_DATE);
            hdr->insertTime(HDR_DATE, squid_curtime);
        } else if (http->storeEntry()->timestamp < squid_curtime) {
            hdr->putInt(HDR_AGE,
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
                hdr->putStr(HDR_WARNING, tbuf);
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
    if ( !hdr->has(HDR_DATE) ) {
        if (!http->storeEntry())
            hdr->insertTime(HDR_DATE, squid_curtime);
        else if (http->storeEntry()->timestamp > 0)
            hdr->insertTime(HDR_DATE, http->storeEntry()->timestamp);
        else {
            debugs(88,DBG_IMPORTANT,"WARNING: An error inside Squid has caused an HTTP reply without Date:. Please report this:");
            /* dump something useful about the problem */
            http->storeEntry()->dump(DBG_IMPORTANT);
        }
    }

    // add Warnings required by RFC 2616 if serving a stale hit
    if (http->request->flags.stale_if_hit && logTypeIsATcpHit(http->logType)) {
        hdr->putWarning(110, "Response is stale");
        if (http->request->flags.need_validation)
            hdr->putWarning(111, "Revalidation failed");
    }

    /* Filter unproxyable authentication types */

    if (http->logType != LOG_TCP_DENIED &&
            hdr->has(HDR_WWW_AUTHENTICATE)) {
        HttpHeaderPos pos = HttpHeaderInitPos;
        HttpHeaderEntry *e;

        int connection_auth_blocked = 0;
        while ((e = hdr->getEntry(&pos))) {
            if (e->id == HDR_WWW_AUTHENTICATE) {
                const char *value = e->value.rawBuf();

                if ((strncasecmp(value, "NTLM", 4) == 0 &&
                        (value[4] == '\0' || value[4] == ' '))
                        ||
                        (strncasecmp(value, "Negotiate", 9) == 0 &&
                         (value[9] == '\0' || value[9] == ' '))
                        ||
                        (strncasecmp(value, "Kerberos", 8) == 0 &&
                         (value[8] == '\0' || value[8] == ' '))) {
                    if (request->flags.connection_auth_disabled) {
                        hdr->delAt(pos, connection_auth_blocked);
                        continue;
                    }
                    request->flags.must_keepalive = 1;
                    if (!request->flags.accelerated && !request->flags.intercepted) {
                        httpHeaderPutStrf(hdr, HDR_PROXY_SUPPORT, "Session-Based-Authentication");
                        /*
                          We send "[Proxy-]Connection: Proxy-Support" header to mark
                          Proxy-Support as a hop-by-hop header for intermediaries that do not
                          understand the semantics of this header. The RFC should have included
                          this recommendation.
                        */
                        httpHeaderPutStrf(hdr, HDR_CONNECTION, "Proxy-support");
                    }
                    break;
                }
            }
        }

        if (connection_auth_blocked)
            hdr->refreshMask();
    }

    /* Handle authentication headers */
    if (http->logType == LOG_TCP_DENIED &&
            ( reply->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED ||
              reply->sline.status == HTTP_UNAUTHORIZED)
       ) {
        /* Add authentication header */
        /*! \todo alter errorstate to be accel on|off aware. The 0 on the next line
         * depends on authenticate behaviour: all schemes to date send no extra
         * data on 407/401 responses, and do not check the accel state on 401/407
         * responses
         */
        authenticateFixHeader(reply, request->auth_user_request, request, 0, 1);
    } else if (request->auth_user_request)
        authenticateFixHeader(reply, request->auth_user_request, request,
                              http->flags.accel, 0);

    /* Append X-Cache */
    httpHeaderPutStrf(hdr, HDR_X_CACHE, "%s from %s",
                      is_hit ? "HIT" : "MISS", getMyHostname());

#if USE_CACHE_DIGESTS
    /* Append X-Cache-Lookup: -- temporary hack, to be removed @?@ @?@ */
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
        request->flags.proxy_keepalive = 0;
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
                 reply->sline.version.major,
                 reply->sline.version.minor,
                 ThisCache);
        strListAdd(&strVia, bbuf, ',');
        hdr->delById(HDR_VIA);
        hdr->putStr(HDR_VIA, strVia.termedBuf());
    }
    /* Signal keep-alive or close explicitly */
    hdr->putStr(HDR_CONNECTION, request->flags.proxy_keepalive ? "keep-alive" : "close");

#if ADD_X_REQUEST_URI
    /*
     * Knowing the URI of the request is useful when debugging persistent
     * connections in a client; we cannot guarantee the order of http headers,
     * but X-Request-URI is likely to be the very last header to ease use from a
     * debugger [hdr->entries.count-1].
     */
    hdr->putStr(HDR_X_REQUEST_URI,
                http->memOjbect()->url ? http->memObject()->url : http->uri);

#endif

    httpHdrMangleList(hdr, request, ROR_REPLY);
}