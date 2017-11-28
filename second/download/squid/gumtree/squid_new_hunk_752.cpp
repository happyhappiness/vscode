    assert (http->getConn() != NULL);
    deRegisterWithConn();
    /* we can't handle any more stream data - detach */
    clientStreamDetach(getTail(), http);
}

ClientSocketContext::ClientSocketContext(const Comm::ConnectionPointer &aConn, ClientHttpRequest *aReq) :
    clientConnection(aConn),
    http(aReq),
    reply(NULL),
    next(NULL),
    writtenToSocket(0),
    mayUseConnection_ (false),
    connRegistered_ (false)
{
    assert(http != NULL);
    memset (reqbuf, '\0', sizeof (reqbuf));
    flags.deferred = 0;
    flags.parsed_ok = 0;
    deferredparams.node = NULL;
    deferredparams.rep = NULL;
}

void
ClientSocketContext::writeControlMsg(HttpControlMsg &msg)
{
    HttpReply::Pointer rep(msg.reply);
    Must(rep != NULL);

    // remember the callback
    cbControlMsgSent = msg.cbSuccess;

    AsyncCall::Pointer call = commCbCall(33, 5, "ClientSocketContext::wroteControlMsg",
                                         CommIoCbPtrFun(&WroteControlMsg, this));

    if (!getConn()->writeControlMsgAndCall(this, rep.getRaw(), call)) {
        // but still inform the caller (so it may resume its operation)
        doneWithControlMsg();
    }
}

void
ClientSocketContext::doneWithControlMsg()
{
    ScheduleCallHere(cbControlMsgSent);
    cbControlMsgSent = NULL;

    debugs(33, 3, clientConnection << ": calling PushDeferredIfNeeded after control msg wrote");
    ClientSocketContextPushDeferredIfNeeded(this, getConn());

}

/// called when we wrote the 1xx response
void
ClientSocketContext::wroteControlMsg(const Comm::ConnectionPointer &conn, char *, size_t, Comm::Flag errflag, int xerrno)
{
    if (errflag == Comm::ERR_CLOSING)
        return;

    if (errflag == Comm::OK) {
        doneWithControlMsg();
        return;
    }

    debugs(33, 3, HERE << "1xx writing failed: " << xstrerr(xerrno));
    // no error notification: see HttpControlMsg.h for rationale and
    // note that some errors are detected elsewhere (e.g., close handler)

    // close on 1xx errors to be conservative and to simplify the code
    // (if we do not close, we must notify the source of a failure!)
    conn->close();

    // XXX: writeControlMsgAndCall() should handle writer-specific writing
    // results, including errors and then call us with success/failure outcome.
}

/// wroteControlMsg() wrapper: ClientSocketContext is not an AsyncJob
void
ClientSocketContext::WroteControlMsg(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, Comm::Flag errflag, int xerrno, void *data)
{
    ClientSocketContext *context = static_cast<ClientSocketContext*>(data);
    context->wroteControlMsg(conn, bufnotused, size, errflag, xerrno);
}

#if USE_IDENT
