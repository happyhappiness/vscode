    flags.parsed_ok = 0;
    deferredparams.node = NULL;
    deferredparams.rep = NULL;
}

ClientSocketContext *
ClientSocketContextNew(const Comm::ConnectionPointer &client, ClientHttpRequest * http)
{
    ClientSocketContext *newContext;
    assert(http != NULL);
    newContext = new ClientSocketContext;
    newContext->http = http;
    newContext->clientConnection = client;
    return newContext;
}

void
ClientSocketContext::writeControlMsg(HttpControlMsg &msg)
{
    HttpReply *rep = msg.reply;
    Must(rep);

    // apply selected clientReplyContext::buildReplyHeader() mods
    // it is not clear what headers are required for control messages
    rep->header.removeHopByHopEntries();
    rep->header.putStr(HDR_CONNECTION, "keep-alive");
    httpHdrMangleList(&rep->header, http->request, ROR_REPLY);

    // remember the callback
    cbControlMsgSent = msg.cbSuccess;

    MemBuf *mb = rep->pack();

    debugs(11, 2, "HTTP Client " << clientConnection);
    debugs(11, 2, "HTTP Client CONTROL MSG:\n---------\n" << mb->buf << "\n----------");

    AsyncCall::Pointer call = commCbCall(33, 5, "ClientSocketContext::wroteControlMsg",
                                         CommIoCbPtrFun(&WroteControlMsg, this));
    Comm::Write(clientConnection, mb, call);

    delete mb;
}

/// called when we wrote the 1xx response
void
ClientSocketContext::wroteControlMsg(const Comm::ConnectionPointer &conn, char *, size_t, comm_err_t errflag, int xerrno)
{
    if (errflag == COMM_ERR_CLOSING)
        return;

    if (errflag == COMM_OK) {
        ScheduleCallHere(cbControlMsgSent);
        return;
    }

    debugs(33, 3, HERE << "1xx writing failed: " << xstrerr(xerrno));
    // no error notification: see HttpControlMsg.h for rationale and
    // note that some errors are detected elsewhere (e.g., close handler)

    // close on 1xx errors to be conservative and to simplify the code
    // (if we do not close, we must notify the source of a failure!)
    conn->close();
}

/// wroteControlMsg() wrapper: ClientSocketContext is not an AsyncJob
void
ClientSocketContext::WroteControlMsg(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, comm_err_t errflag, int xerrno, void *data)
{
    ClientSocketContext *context = static_cast<ClientSocketContext*>(data);
    context->wroteControlMsg(conn, bufnotused, size, errflag, xerrno);
}

#if USE_IDENT
static void
clientIdentDone(const char *ident, void *data)
{
    ConnStateData *conn = (ConnStateData *)data;
    xstrncpy(conn->clientConnection->rfc931, ident ? ident : dash_str, USER_IDENT_SZ);
}
#endif

void
clientUpdateStatCounters(log_type logType)
{
    ++statCounter.client_http.requests;

    if (logTypeIsATcpHit(logType))
        ++statCounter.client_http.hits;

    if (logType == LOG_TCP_HIT)
        ++statCounter.client_http.disk_hits;
    else if (logType == LOG_TCP_MEM_HIT)
        ++statCounter.client_http.mem_hits;
}

void
clientUpdateStatHistCounters(log_type logType, int svc_time)
{
    statCounter.client_http.allSvcTime.count(svc_time);
    /**
     * The idea here is not to be complete, but to get service times
     * for only well-defined types.  For example, we don't include
     * LOG_TCP_REFRESH_FAIL because its not really a cache hit
     * (we *tried* to validate it, but failed).
     */

    switch (logType) {

    case LOG_TCP_REFRESH_UNMODIFIED:
        statCounter.client_http.nearHitSvcTime.count(svc_time);
        break;

    case LOG_TCP_IMS_HIT:
        statCounter.client_http.nearMissSvcTime.count(svc_time);
        break;

    case LOG_TCP_HIT:

    case LOG_TCP_MEM_HIT:

    case LOG_TCP_OFFLINE_HIT:
        statCounter.client_http.hitSvcTime.count(svc_time);
        break;

    case LOG_TCP_MISS:

    case LOG_TCP_CLIENT_REFRESH_MISS:
        statCounter.client_http.missSvcTime.count(svc_time);
        break;

    default:
        /* make compiler warnings go away */
        break;
    }
