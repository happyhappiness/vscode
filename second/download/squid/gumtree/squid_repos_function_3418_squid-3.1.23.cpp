void
ClientHttpRequest::logRequest()
{
    if (out.size || logType) {
        al.icp.opcode = ICP_INVALID;
        al.url = log_uri;
        debugs(33, 9, "clientLogRequest: al.url='" << al.url << "'");

        if (al.reply) {
            al.http.code = al.reply->sline.status;
            al.http.content_type = al.reply->content_type.termedBuf();
        } else if (loggingEntry() && loggingEntry()->mem_obj) {
            al.http.code = loggingEntry()->mem_obj->getReply()->sline.status;
            al.http.content_type = loggingEntry()->mem_obj->getReply()->content_type.termedBuf();
        }

        debugs(33, 9, "clientLogRequest: http.code='" << al.http.code << "'");

        if (loggingEntry() && loggingEntry()->mem_obj)
            al.cache.objectSize = loggingEntry()->contentLen();

        al.cache.caddr.SetNoAddr();

        if (getConn() != NULL) al.cache.caddr = getConn()->log_addr;

        al.cache.requestSize = req_sz;
        al.cache.requestHeadersSize = req_sz;

        al.cache.replySize = out.size;
        al.cache.replyHeadersSize = out.headers_sz;

        al.cache.highOffset = out.offset;

        al.cache.code = logType;

        al.cache.msec = tvSubMsec(start_time, current_time);

        if (request)
            prepareLogWithRequestDetails(request, &al);

        if (getConn() != NULL && getConn()->rfc931[0])
            al.cache.rfc931 = getConn()->rfc931;

#if USE_SSL && 0

        /* This is broken. Fails if the connection has been closed. Needs
         * to snarf the ssl details some place earlier..
         */
        if (getConn() != NULL)
            al.cache.ssluser = sslGetUserEmail(fd_table[getConn()->fd].ssl);

#endif

        ACLFilledChecklist *checklist = clientAclChecklistCreate(Config.accessList.log, this);

        if (al.reply)
            checklist->reply = HTTPMSGLOCK(al.reply);

        if (!Config.accessList.log || checklist->fastCheck()) {
            if (request)
                al.adapted_request = HTTPMSGLOCK(request);
            accessLogLog(&al, checklist);
            updateCounters();

            if (getConn() != NULL)
                clientdbUpdate(getConn()->peer, logType, PROTO_HTTP, out.size);
        }

        delete checklist;
    }

    accessLogFreeMemory(&al);
}