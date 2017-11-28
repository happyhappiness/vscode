void
ClientHttpRequest::logRequest()
{
    if (!out.size && !logType)
        debugs(33, 5, HERE << "logging half-baked transaction: " << log_uri);

    al->icp.opcode = ICP_INVALID;
    al->url = log_uri;
    debugs(33, 9, "clientLogRequest: al.url='" << al->url << "'");

    if (al->reply) {
        al->http.code = al->reply->sline.status();
        al->http.content_type = al->reply->content_type.termedBuf();
    } else if (loggingEntry() && loggingEntry()->mem_obj) {
        al->http.code = loggingEntry()->mem_obj->getReply()->sline.status();
        al->http.content_type = loggingEntry()->mem_obj->getReply()->content_type.termedBuf();
    }

    debugs(33, 9, "clientLogRequest: http.code='" << al->http.code << "'");

    if (loggingEntry() && loggingEntry()->mem_obj)
        al->cache.objectSize = loggingEntry()->contentLen();

    al->cache.caddr.setNoAddr();

    if (getConn() != NULL) {
        al->cache.caddr = getConn()->log_addr;
        al->cache.port =  cbdataReference(getConn()->port);
    }

    al->cache.requestSize = req_sz;
    al->cache.requestHeadersSize = req_sz;

    al->cache.replySize = out.size;
    al->cache.replyHeadersSize = out.headers_sz;

    al->cache.highOffset = out.offset;

    al->cache.code = logType;

    al->cache.msec = tvSubMsec(start_time, current_time);

    if (request)
        prepareLogWithRequestDetails(request, al);

    if (getConn() != NULL && getConn()->clientConnection != NULL && getConn()->clientConnection->rfc931[0])
        al->cache.rfc931 = getConn()->clientConnection->rfc931;

#if USE_SSL && 0

    /* This is broken. Fails if the connection has been closed. Needs
     * to snarf the ssl details some place earlier..
     */
    if (getConn() != NULL)
        al->cache.ssluser = sslGetUserEmail(fd_table[getConn()->fd].ssl);

#endif

    /*Add notes*/
    // The al->notes and request->notes must point to the same object.
    (void)SyncNotes(*al, *request);
    typedef Notes::iterator ACAMLI;
    for (ACAMLI i = Config.notes.begin(); i != Config.notes.end(); ++i) {
        if (const char *value = (*i)->match(request, al->reply)) {
            NotePairs &notes = SyncNotes(*al, *request);
            notes.add((*i)->key.termedBuf(), value);
            debugs(33, 3, HERE << (*i)->key.termedBuf() << " " << value);
        }
    }

    ACLFilledChecklist checklist(NULL, request, NULL);
    if (al->reply) {
        checklist.reply = al->reply;
        HTTPMSGLOCK(checklist.reply);
    }

    if (request) {
        al->adapted_request = request;
        HTTPMSGLOCK(al->adapted_request);
    }
    accessLogLog(al, &checklist);

    bool updatePerformanceCounters = true;
    if (Config.accessList.stats_collection) {
        ACLFilledChecklist statsCheck(Config.accessList.stats_collection, request, NULL);
        if (al->reply) {
            statsCheck.reply = al->reply;
            HTTPMSGLOCK(statsCheck.reply);
        }
        updatePerformanceCounters = (statsCheck.fastCheck() == ACCESS_ALLOWED);
    }

    if (updatePerformanceCounters) {
        if (request)
            updateCounters();

        if (getConn() != NULL && getConn()->clientConnection != NULL)
            clientdbUpdate(getConn()->clientConnection->remote, logType, AnyP::PROTO_HTTP, out.size);
    }
}