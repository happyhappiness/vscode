static void
clientInterpretRequestHeaders(ClientHttpRequest * http)
{
    HttpRequest *request = http->request;
    HttpHeader *req_hdr = &request->header;
    int no_cache = 0;
    const char *str;

    request->imslen = -1;
    request->ims = req_hdr->getTime(HDR_IF_MODIFIED_SINCE);

    if (request->ims > 0)
        request->flags.ims = 1;

    if (!request->flags.ignore_cc) {
        if (req_hdr->has(HDR_PRAGMA)) {
            String s = req_hdr->getList(HDR_PRAGMA);

            if (strListIsMember(&s, "no-cache", ','))
                no_cache++;

            s.clean();
        }

        if (request->cache_control)
            if (EBIT_TEST(request->cache_control->mask, CC_NO_CACHE))
                no_cache++;

        /*
        * Work around for supporting the Reload button in IE browsers when Squid
        * is used as an accelerator or transparent proxy, by turning accelerated
        * IMS request to no-cache requests. Now knows about IE 5.5 fix (is
        * actually only fixed in SP1, but we can't tell whether we are talking to
        * SP1 or not so all 5.5 versions are treated 'normally').
        */
        if (Config.onoff.ie_refresh) {
            if (http->flags.accel && request->flags.ims) {
                if ((str = req_hdr->getStr(HDR_USER_AGENT))) {
                    if (strstr(str, "MSIE 5.01") != NULL)
                        no_cache++;
                    else if (strstr(str, "MSIE 5.0") != NULL)
                        no_cache++;
                    else if (strstr(str, "MSIE 4.") != NULL)
                        no_cache++;
                    else if (strstr(str, "MSIE 3.") != NULL)
                        no_cache++;
                }
            }
        }
    }

    if (request->method == METHOD_OTHER) {
        no_cache++;
    }

    if (no_cache) {
#if HTTP_VIOLATIONS

        if (Config.onoff.reload_into_ims)
            request->flags.nocache_hack = 1;
        else if (refresh_nocache_hack)
            request->flags.nocache_hack = 1;
        else
#endif

            request->flags.nocache = 1;
    }

    /* ignore range header in non-GETs or non-HEADs */
    if (request->method == METHOD_GET || request->method == METHOD_HEAD) {
        // XXX: initialize if we got here without HttpRequest::parseHeader()
        if (!request->range)
            request->range = req_hdr->getRange();

        if (request->range) {
            request->flags.range = 1;
            clientStreamNode *node = (clientStreamNode *)http->client_stream.tail->data;
            /* XXX: This is suboptimal. We should give the stream the range set,
             * and thereby let the top of the stream set the offset when the
             * size becomes known. As it is, we will end up requesting from 0
             * for evey -X range specification.
             * RBC - this may be somewhat wrong. We should probably set the range
             * iter up at this point.
             */
            node->readBuffer.offset = request->range->lowestOffset(0);
            http->range_iter.pos = request->range->begin();
            http->range_iter.valid = true;
        }
    }

    /* Only HEAD and GET requests permit a Range or Request-Range header.
     * If these headers appear on any other type of request, delete them now.
     */
    else {
        req_hdr->delById(HDR_RANGE);
        req_hdr->delById(HDR_REQUEST_RANGE);
        delete request->range;
        request->range = NULL;
    }

    if (req_hdr->has(HDR_AUTHORIZATION))
        request->flags.auth = 1;

    ConnStateData *http_conn = http->getConn();
    if (http_conn) {
        request->flags.connection_auth_disabled = http_conn->port->connection_auth_disabled;
        if (!request->flags.connection_auth_disabled) {
            if (http_conn->pinning.fd != -1) {
                if (http_conn->pinning.auth) {
                    request->flags.connection_auth = 1;
                    request->flags.auth = 1;
                } else {
                    request->flags.connection_proxy_auth = 1;
                }
                request->setPinnedConnection(http_conn);
            }
        }
    } else {
        // internal requests and ESI don't have client conn.
        request->flags.connection_auth_disabled = 1;
    }

    /* check if connection auth is used, and flag as candidate for pinning
     * in such case.
     * Note: we may need to set flags.connection_auth even if the connection
     * is already pinned if it was pinned earlier due to proxy auth
     */
    if (!request->flags.connection_auth) {
        if (req_hdr->has(HDR_AUTHORIZATION) || req_hdr->has(HDR_PROXY_AUTHORIZATION)) {
            HttpHeaderPos pos = HttpHeaderInitPos;
            HttpHeaderEntry *e;
            int may_pin = 0;
            while ((e = req_hdr->getEntry(&pos))) {
                if (e->id == HDR_AUTHORIZATION || e->id == HDR_PROXY_AUTHORIZATION) {
                    const char *value = e->value.rawBuf();
                    if (strncasecmp(value, "NTLM ", 5) == 0
                            ||
                            strncasecmp(value, "Negotiate ", 10) == 0
                            ||
                            strncasecmp(value, "Kerberos ", 9) == 0) {
                        if (e->id == HDR_AUTHORIZATION) {
                            request->flags.connection_auth = 1;
                            may_pin = 1;
                        } else {
                            request->flags.connection_proxy_auth = 1;
                            may_pin = 1;
                        }
                    }
                }
            }
            if (may_pin && !request->pinnedConnection()) {
                request->setPinnedConnection(http->getConn());
            }
        }
    }


    if (request->login[0] != '\0')
        request->flags.auth = 1;

    if (req_hdr->has(HDR_VIA)) {
        String s = req_hdr->getList(HDR_VIA);
        /*
         * ThisCache cannot be a member of Via header, "1.0 ThisCache" can.
         * Note ThisCache2 has a space prepended to the hostname so we don't
         * accidentally match super-domains.
         */

        if (strListIsSubstr(&s, ThisCache2, ',')) {
            debugObj(33, 1, "WARNING: Forwarding loop detected for:\n",
                     request, (ObjPackMethod) & httpRequestPack);
            request->flags.loopdetect = 1;
        }

#if FORW_VIA_DB
        fvdbCountVia(s.termedBuf());

#endif

        s.clean();
    }

    /**
     \todo  --enable-useragent-log and --enable-referer-log. We should
            probably drop those two as the custom log formats accomplish pretty much the same thing..
    */
#if USE_USERAGENT_LOG
    if ((str = req_hdr->getStr(HDR_USER_AGENT)))
        logUserAgent(fqdnFromAddr(http->getConn()->log_addr), str);

#endif
#if USE_REFERER_LOG

    if ((str = req_hdr->getStr(HDR_REFERER)))
        logReferer(fqdnFromAddr(http->getConn()->log_addr), str, http->log_uri);

#endif
#if FORW_VIA_DB

    if (req_hdr->has(HDR_X_FORWARDED_FOR)) {
        String s = req_hdr->getList(HDR_X_FORWARDED_FOR);
        fvdbCountForw(s.termedBuf());
        s.clean();
    }

#endif

    request->flags.cachable = http->request->cacheable();

    if (clientHierarchical(http))
        request->flags.hierarchical = 1;

    debugs(85, 5, "clientInterpretRequestHeaders: REQ_NOCACHE = " <<
           (request->flags.nocache ? "SET" : "NOT SET"));
    debugs(85, 5, "clientInterpretRequestHeaders: REQ_CACHABLE = " <<
           (request->flags.cachable ? "SET" : "NOT SET"));
    debugs(85, 5, "clientInterpretRequestHeaders: REQ_HIERARCHICAL = " <<
           (request->flags.hierarchical ? "SET" : "NOT SET"));

}