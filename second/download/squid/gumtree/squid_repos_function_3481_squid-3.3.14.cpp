void
prepareLogWithRequestDetails(HttpRequest * request, AccessLogEntry::Pointer &aLogEntry)
{
    assert(request);
    assert(aLogEntry != NULL);

    if (Config.onoff.log_mime_hdrs) {
        Packer p;
        MemBuf mb;
        mb.init();
        packerToMemInit(&p, &mb);
        request->header.packInto(&p);
        //This is the request after adaptation or redirection
        aLogEntry->headers.adapted_request = xstrdup(mb.buf);

        // the virgin request is saved to aLogEntry->request
        if (aLogEntry->request) {
            packerClean(&p);
            mb.reset();
            packerToMemInit(&p, &mb);
            aLogEntry->request->header.packInto(&p);
            aLogEntry->headers.request = xstrdup(mb.buf);
        }

#if USE_ADAPTATION
        const Adaptation::History::Pointer ah = request->adaptLogHistory();
        if (ah != NULL) {
            packerClean(&p);
            mb.reset();
            packerToMemInit(&p, &mb);
            ah->lastMeta.packInto(&p);
            aLogEntry->adapt.last_meta = xstrdup(mb.buf);
        }
#endif

        packerClean(&p);
        mb.clean();
    }

#if ICAP_CLIENT
    const Adaptation::Icap::History::Pointer ih = request->icapHistory();
    if (ih != NULL)
        aLogEntry->icap.processingTime = ih->processingTime();
#endif

    aLogEntry->http.method = request->method;
    aLogEntry->http.version = request->http_ver;
    aLogEntry->hier = request->hier;
    if (request->content_length > 0) // negative when no body or unknown length
        aLogEntry->cache.requestSize += request->content_length;
    aLogEntry->cache.extuser = request->extacl_user.termedBuf();

    // Adapted request, if any, inherits and then collects all the stats, but
    // the virgin request gets logged instead; copy the stats to log them.
    // TODO: avoid losses by keeping these stats in a shared history object?
    if (aLogEntry->request) {
        aLogEntry->request->dnsWait = request->dnsWait;
        aLogEntry->request->errType = request->errType;
        aLogEntry->request->errDetail = request->errDetail;
    }
}