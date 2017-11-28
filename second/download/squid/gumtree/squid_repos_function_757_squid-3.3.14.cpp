static void
clientInterpretRequestHeaders(ClientHttpRequest * http)
{
    HttpRequest *request = http->request;
    HttpHeader *req_hdr = &request->header;
    bool no_cache = false;
    const char *str;

    request->imslen = -1;
    request->ims = req_hdr->getTime(HDR_IF_MODIFIED_SINCE);

    if (request->ims > 0)
        request->flags.ims = 1;

    if (!request->flags.ignoreCc) {
        if (request->cache_control) {
            if (request->cache_control->hasNoCache())
                no_cache=true;

            // RFC 2616: treat Pragma:no-cache as if it was Cache-Control:no-cache when Cache-Control is missing
        } else if (req_hdr->has(HDR_PRAGMA))
            no_cache = req_hdr->hasListMember(HDR_PRAGMA,"no-cache",',');

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
                        no_cache=true;
                    else if (strstr(str, "MSIE 5.0") != NULL)
                        no_cache=true;
                    else if (strstr(str, "MSIE 4.") != NULL)
                        no_cache=true;
                    else if (strstr(str, "MSIE 3.") != NULL)
                        no_cache=true;
                }
            }
        }
    }

    if (request->method == METHOD_OTHER) {
        no_cache=true;
    }

    if (no_cache) {
#if USE_HTTP_VIOLATIONS

        if (Config.onoff.reload_into_ims)
            request->flags.nocacheHack = 1;
        else if (refresh_nocache_hack)
            request->flags.nocacheHack = 1;
        else
#endif

            request->flags.noCache = 1;
    }

    /* ignore range header in non-GETs or non-HEADs */
    if (request->method == METHOD_GET || request->method == METHOD_HEAD) {
        // XXX: initialize if we got here without HttpRequest::parseHeader()
        if (!request->range)
            request->range = req_hdr->getRange();

        if (request->range) {
            request->flags.isRanged=true;
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
        request->ignoreRange("neither HEAD nor GET");
    }

    if (req_hdr->has(HDR_AUTHORIZATION))
        request->flags.auth = 1;

    clientCheckPinning(http);

    if (request->login[0] != '\0')
        request->flags.auth = 1;

    if (req_hdr->has(HDR_VIA)) {
        String s = req_hdr->getList(HDR_VIA);
        /*
         * ThisCache cannot be a member of Via header, "1.1 ThisCache" can.
         * Note ThisCache2 has a space prepended to the hostname so we don't
         * accidentally match super-domains.
         */

        if (strListIsSubstr(&s, ThisCache2, ',')) {
            debugObj(33, 1, "WARNING: Forwarding loop detected for:\n",
                     request, (ObjPackMethod) & httpRequestPack);
            request->flags.loopDetected = 1;
        }

#if USE_FORW_VIA_DB
        fvdbCountVia(s.termedBuf());

#endif

        s.clean();
    }

#if USE_FORW_VIA_DB

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
           (request->flags.noCache ? "SET" : "NOT SET"));
    debugs(85, 5, "clientInterpretRequestHeaders: REQ_CACHABLE = " <<
           (request->flags.cachable ? "SET" : "NOT SET"));
    debugs(85, 5, "clientInterpretRequestHeaders: REQ_HIERARCHICAL = " <<
           (request->flags.hierarchical ? "SET" : "NOT SET"));

}