void
HttpStateData::httpBuildRequestHeader(HttpRequest * request,
                                      StoreEntry * entry,
                                      const AccessLogEntryPointer &al,
                                      HttpHeader * hdr_out,
                                      const HttpStateFlags &flags)
{
    /* building buffer for complex strings */
#define BBUF_SZ (MAX_URL+32)
    LOCAL_ARRAY(char, bbuf, BBUF_SZ);
    LOCAL_ARRAY(char, ntoabuf, MAX_IPSTRLEN);
    const HttpHeader *hdr_in = &request->header;
    const HttpHeaderEntry *e = NULL;
    HttpHeaderPos pos = HttpHeaderInitPos;
    assert (hdr_out->owner == hoRequest);

    /* use our IMS header if the cached entry has Last-Modified time */
    if (request->lastmod > -1)
        hdr_out->putTime(HDR_IF_MODIFIED_SINCE, request->lastmod);

    // Add our own If-None-Match field if the cached entry has a strong ETag.
    // copyOneHeaderFromClientsideRequestToUpstreamRequest() adds client ones.
    if (request->etag.defined()) {
        hdr_out->addEntry(new HttpHeaderEntry(HDR_IF_NONE_MATCH, NULL,
                                              request->etag.termedBuf()));
    }

    bool we_do_ranges = decideIfWeDoRanges (request);

    String strConnection (hdr_in->getList(HDR_CONNECTION));

    while ((e = hdr_in->getEntry(&pos)))
        copyOneHeaderFromClientsideRequestToUpstreamRequest(e, strConnection, request, hdr_out, we_do_ranges, flags);

    /* Abstraction break: We should interpret multipart/byterange responses
     * into offset-length data, and this works around our inability to do so.
     */
    if (!we_do_ranges && request->multipartRangeRequest()) {
        /* don't cache the result */
        request->flags.cachable = 0;
        /* pretend it's not a range request */
        request->ignoreRange("want to request the whole object");
        request->flags.isRanged=false;
    }

    /* append Via */
    if (Config.onoff.via) {
        String strVia;
        strVia = hdr_in->getList(HDR_VIA);
        snprintf(bbuf, BBUF_SZ, "%d.%d %s",
                 request->http_ver.major,
                 request->http_ver.minor, ThisCache);
        strListAdd(&strVia, bbuf, ',');
        hdr_out->putStr(HDR_VIA, strVia.termedBuf());
        strVia.clean();
    }

    if (request->flags.accelerated) {
        /* Append Surrogate-Capabilities */
        String strSurrogate(hdr_in->getList(HDR_SURROGATE_CAPABILITY));
#if USE_SQUID_ESI
        snprintf(bbuf, BBUF_SZ, "%s=\"Surrogate/1.0 ESI/1.0\"", Config.Accel.surrogate_id);
#else
        snprintf(bbuf, BBUF_SZ, "%s=\"Surrogate/1.0\"", Config.Accel.surrogate_id);
#endif
        strListAdd(&strSurrogate, bbuf, ',');
        hdr_out->putStr(HDR_SURROGATE_CAPABILITY, strSurrogate.termedBuf());
    }

    /** \pre Handle X-Forwarded-For */
    if (strcmp(opt_forwarded_for, "delete") != 0) {

        String strFwd = hdr_in->getList(HDR_X_FORWARDED_FOR);

        if (strFwd.size() > 65536/2) {
            // There is probably a forwarding loop with Via detection disabled.
            // If we do nothing, String will assert on overflow soon.
            // TODO: Terminate all transactions with huge XFF?
            strFwd = "error";

            static int warnedCount = 0;
            if (warnedCount++ < 100) {
                const char *url = entry ? entry->url() : urlCanonical(request);
                debugs(11, DBG_IMPORTANT, "Warning: likely forwarding loop with " << url);
            }
        }

        if (strcmp(opt_forwarded_for, "on") == 0) {
            /** If set to ON - append client IP or 'unknown'. */
            if ( request->client_addr.IsNoAddr() )
                strListAdd(&strFwd, "unknown", ',');
            else
                strListAdd(&strFwd, request->client_addr.NtoA(ntoabuf, MAX_IPSTRLEN), ',');
        } else if (strcmp(opt_forwarded_for, "off") == 0) {
            /** If set to OFF - append 'unknown'. */
            strListAdd(&strFwd, "unknown", ',');
        } else if (strcmp(opt_forwarded_for, "transparent") == 0) {
            /** If set to TRANSPARENT - pass through unchanged. */
        } else if (strcmp(opt_forwarded_for, "truncate") == 0) {
            /** If set to TRUNCATE - drop existing list and replace with client IP or 'unknown'. */
            if ( request->client_addr.IsNoAddr() )
                strFwd = "unknown";
            else
                strFwd = request->client_addr.NtoA(ntoabuf, MAX_IPSTRLEN);
        }
        if (strFwd.size() > 0)
            hdr_out->putStr(HDR_X_FORWARDED_FOR, strFwd.termedBuf());
    }
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
        }
    }

    /* append Authorization if known in URL, not in header and going direct */
    if (!hdr_out->has(HDR_AUTHORIZATION)) {
        if (!request->flags.proxying && request->login && *request->login) {
            httpHeaderPutStrf(hdr_out, HDR_AUTHORIZATION, "Basic %s",
                              old_base64_encode(request->login));
        }
    }

    /* Fixup (Proxy-)Authorization special cases. Plain relaying dealt with above */
    httpFixupAuthentication(request, hdr_in, hdr_out, flags);

    /* append Cache-Control, add max-age if not there already */
    {
        HttpHdrCc *cc = hdr_in->getCc();

        if (!cc)
            cc = new HttpHdrCc();

#if 0 /* see bug 2330 */
        /* Set no-cache if determined needed but not found */
        if (request->flags.nocache)
            EBIT_SET(cc->mask, CC_NO_CACHE);
#endif

        /* Add max-age only without no-cache */
        if (!cc->hasMaxAge() && !cc->hasNoCache()) {
            const char *url =
                entry ? entry->url() : urlCanonical(request);
            cc->maxAge(getMaxAge(url));

        }

        /* Enforce sibling relations */
        if (flags.only_if_cached)
            cc->onlyIfCached(true);

        hdr_out->putCc(cc);

        delete cc;
    }

    /* maybe append Connection: keep-alive */
    if (flags.keepalive) {
        hdr_out->putStr(HDR_CONNECTION, "keep-alive");
    }

    /* append Front-End-Https */
    if (flags.front_end_https) {
        if (flags.front_end_https == 1 || request->protocol == AnyP::PROTO_HTTPS)
            hdr_out->putStr(HDR_FRONT_END_HTTPS, "On");
    }

    if (flags.chunked_request) {
        // Do not just copy the original value so that if the client-side
        // starts decode other encodings, this code may remain valid.
        hdr_out->putStr(HDR_TRANSFER_ENCODING, "chunked");
    }

    /* Now mangle the headers. */
    if (Config2.onoff.mangle_request_headers)
        httpHdrMangleList(hdr_out, request, ROR_REQUEST);

    if (Config.request_header_add && !Config.request_header_add->empty())
        httpHdrAdd(hdr_out, request, al, *Config.request_header_add);

    strConnection.clean();
}