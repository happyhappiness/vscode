
ACLFilledChecklist *
clientAclChecklistCreate(const acl_access * acl, ClientHttpRequest * http)
{
    ConnStateData * conn = http->getConn();
    ACLFilledChecklist *ch = new ACLFilledChecklist(acl, http->request,
            cbdataReferenceValid(conn) && conn != NULL && conn->clientConnection != NULL ? conn->clientConnection->rfc931 : dash_str);

    /*
     * hack for ident ACL. It needs to get full addresses, and a place to store
     * the ident result on persistent connections...
     */
    /* connection oriented auth also needs these two lines for it's operation. */
    return ch;
}

CBDATA_CLASS_INIT(ConnStateData);

ConnStateData::ConnStateData() :
        AsyncJob("ConnStateData"),
        switchedToHttps_(false),
        stoppedSending_(NULL),
        stoppedReceiving_(NULL)
{
    pinning.pinned = false;
    pinning.auth = false;
}

bool
ConnStateData::transparent() const
{
    return clientConnection != NULL && (clientConnection->flags & (COMM_TRANSPARENT|COMM_INTERCEPTION));
}

bool
ConnStateData::reading() const
{
    return reader != NULL;
}

void
ConnStateData::stopReading()
{
    if (reading()) {
        comm_read_cancel(clientConnection->fd, reader);
        reader = NULL;
    }
}


BodyPipe::Pointer
ConnStateData::expectRequestBody(int64_t size)
{
    bodyPipe = new BodyPipe(this);
    if (size >= 0)
        bodyPipe->setBodySize(size);
    else
        startDechunkingRequest();
    return bodyPipe;
}

int64_t
ConnStateData::mayNeedToReadMoreBody() const
{
    if (!bodyPipe)
        return 0; // request without a body or read/produced all body bytes

    if (!bodyPipe->bodySizeKnown())
        return -1; // probably need to read more, but we cannot be sure

    const int64_t needToProduce = bodyPipe->unproducedSize();
    const int64_t haveAvailable = static_cast<int64_t>(in.notYetUsed);

    if (needToProduce <= haveAvailable)
        return 0; // we have read what we need (but are waiting for pipe space)

    return needToProduce - haveAvailable;
}

void
ConnStateData::stopReceiving(const char *error)
{
    debugs(33, 4, HERE << "receiving error (" << clientConnection << "): " << error <<
           "; old sending error: " <<
           (stoppedSending() ? stoppedSending_ : "none"));

    if (const char *oldError = stoppedReceiving()) {
        debugs(33, 3, HERE << "already stopped receiving: " << oldError);
        return; // nothing has changed as far as this connection is concerned
    }

    stoppedReceiving_ = error;

    if (const char *sendError = stoppedSending()) {
        debugs(33, 3, HERE << "closing because also stopped sending: " << sendError);
        clientConnection->close();
    }
}

void
ConnStateData::expectNoForwarding()
{
    if (bodyPipe != NULL) {
        debugs(33, 4, HERE << "no consumer for virgin body " << bodyPipe->status());
        bodyPipe->expectNoConsumption();
    }
}

/// initialize dechunking state
void
ConnStateData::startDechunkingRequest()
{
    Must(bodyPipe != NULL);
    debugs(33, 5, HERE << "start dechunking" << bodyPipe->status());
    assert(!in.bodyParser);
    in.bodyParser = new ChunkedCodingParser;
}

/// put parsed content into input buffer and clean up
void
ConnStateData::finishDechunkingRequest(bool withSuccess)
{
    debugs(33, 5, HERE << "finish dechunking: " << withSuccess);

    if (bodyPipe != NULL) {
        debugs(33, 7, HERE << "dechunked tail: " << bodyPipe->status());
        BodyPipe::Pointer myPipe = bodyPipe;
        stopProducingFor(bodyPipe, withSuccess); // sets bodyPipe->bodySize()
        Must(!bodyPipe); // we rely on it being nil after we are done with body
        if (withSuccess) {
            Must(myPipe->bodySizeKnown());
            ClientSocketContext::Pointer context = getCurrentContext();
            if (context != NULL && context->http && context->http->request)
                context->http->request->setContentLength(myPipe->bodySize());
        }
    }

    delete in.bodyParser;
    in.bodyParser = NULL;
}

char *
ConnStateData::In::addressToReadInto() const
{
    return buf + notYetUsed;
}

ConnStateData::In::In() : bodyParser(NULL),
        buf (NULL), notYetUsed (0), allocatedSize (0)
{}

ConnStateData::In::~In()
{
    if (allocatedSize)
        memFreeBuf(allocatedSize, buf);
    delete bodyParser; // TODO: pool
}

void
ConnStateData::sendControlMsg(HttpControlMsg msg)
{
    if (!isOpen()) {
        debugs(33, 3, HERE << "ignoring 1xx due to earlier closure");
        return;
    }

    ClientSocketContext::Pointer context = getCurrentContext();
    if (context != NULL) {
        context->writeControlMsg(msg); // will call msg.cbSuccess
        return;
    }

    debugs(33, 3, HERE << " closing due to missing context for 1xx");
    clientConnection->close();
}

/* This is a comm call normally scheduled by comm_close() */
void
ConnStateData::clientPinnedConnectionClosed(const CommCloseCbParams &io)
{
    unpinConnection();
}

void
ConnStateData::pinConnection(const Comm::ConnectionPointer &pinServer, HttpRequest *request, struct peer *aPeer, bool auth)
{
    char desc[FD_DESC_SZ];

    if (Comm::IsConnOpen(pinning.serverConnection)) {
        if (pinning.serverConnection->fd == pinServer->fd)
            return;
    }
    unpinConnection(); // clears fields ready for re-use. Prevent close() scheduling our close handler.

    pinning.serverConnection = pinServer;
    pinning.host = xstrdup(request->GetHost());
    pinning.port = request->port;
    pinning.pinned = true;
    if (aPeer)
        pinning.peer = cbdataReference(aPeer);
    pinning.auth = auth;
    char stmp[MAX_IPSTRLEN];
    snprintf(desc, FD_DESC_SZ, "%s pinned connection for %s (%d)",
             (auth || !aPeer) ? request->GetHost() : aPeer->name, clientConnection->remote.ToURL(stmp,MAX_IPSTRLEN), clientConnection->fd);
    fd_note(pinning.serverConnection->fd, desc);

    typedef CommCbMemFunT<ConnStateData, CommCloseCbParams> Dialer;
    pinning.closeHandler = JobCallback(33, 5,
                                       Dialer, this, ConnStateData::clientPinnedConnectionClosed);
    comm_add_close_handler(pinning.serverConnection->fd, pinning.closeHandler);
}

const Comm::ConnectionPointer
ConnStateData::validatePinnedConnection(HttpRequest *request, const struct peer *aPeer)
{
    bool valid = true;
    if (!Comm::IsConnOpen(pinning.serverConnection))
        valid = false;
    if (pinning.auth && request && strcasecmp(pinning.host, request->GetHost()) != 0) {
        valid = false;
    }
    if (request && pinning.port != request->port) {
        valid = false;
    }
