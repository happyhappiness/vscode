void
prepareLogWithRequestDetails(HttpRequest * request, AccessLogEntry * aLogEntry)
{
    assert(request);
    assert(aLogEntry);

#if ICAP_CLIENT
    Adaptation::Icap::History::Pointer ih = request->icapHistory();
#endif
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

#if ICAP_CLIENT
        packerClean(&p);
        mb.reset();
        packerToMemInit(&p, &mb);

        if (ih != NULL)
            ih->lastIcapHeader.packInto(&p);
        aLogEntry->headers.icap = xstrdup(mb.buf);
#endif

        packerClean(&p);
        mb.clean();
    }

#if ICAP_CLIENT
    if (ih != NULL)
        aLogEntry->icap.processingTime = ih->processingTime();
#endif

    aLogEntry->http.method = request->method;
    aLogEntry->http.version = request->http_ver;
    aLogEntry->hier = request->hier;
    if (request->content_length > 0) // negative when no body or unknown length
        aLogEntry->cache.requestSize += request->content_length;
    aLogEntry->cache.extuser = request->extacl_user.termedBuf();

    if (request->auth_user_request) {

        if (request->auth_user_request->username())
            aLogEntry->cache.authuser =
                xstrdup(request->auth_user_request->username());

        AUTHUSERREQUESTUNLOCK(request->auth_user_request, "request via clientPrepareLogWithRequestDetails");
    }
}