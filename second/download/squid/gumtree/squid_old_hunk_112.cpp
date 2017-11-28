
ACLFilledChecklist *
clientAclChecklistCreate(const acl_access * acl, ClientHttpRequest * http)
{
    ConnStateData * conn = http->getConn();
    ACLFilledChecklist *ch = new ACLFilledChecklist(acl, http->request,
            cbdataReferenceValid(conn) && conn != NULL ? conn->rfc931 : dash_str);

    /*
     * hack for ident ACL. It needs to get full addresses, and a place to store
     * the ident result on persistent connections...
     */
    /* connection oriented auth also needs these two lines for it's operation. */
    /*
     * Internal requests do not have a connection reference, because: A) their
     * byte count may be transformed before being applied to an outbound
     * connection B) they are internal - any limiting on them should be done on
     * the server end.
     */

    if (conn != NULL)
        ch->conn(conn);	/* unreferenced in FilledCheckList.cc */

    return ch;
}

CBDATA_CLASS_INIT(ConnStateData);

ConnStateData::ConnStateData() :AsyncJob("ConnStateData"), transparent_ (false),
        switchedToHttps_(false),
        stoppedSending_(NULL), stoppedReceiving_(NULL)
{
    pinning.fd = -1;
    pinning.pinned = false;
    pinning.auth = false;
}

bool
ConnStateData::transparent() const
{
    return transparent_;
}

void
ConnStateData::transparent(bool const anInt)
{
    transparent_ = anInt;
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
        comm_read_cancel(fd, reader);
        reader = NULL;
    }
}


BodyPipe::Pointer
ConnStateData::expectRequestBody(int64_t size)
{
    bodyPipe = new BodyPipe(this);
    bodyPipe->setBodySize(size);
    return bodyPipe;
}

void
ConnStateData::stopReceiving(const char *error)
{
    debugs(33, 4, HERE << "receiving error (FD " << fd << "): " << error <<
           "; old sending error: " <<
           (stoppedSending() ? stoppedSending_ : "none"));

    if (const char *oldError = stoppedReceiving()) {
        debugs(33, 3, HERE << "already stopped receiving: " << oldError);
        return; // nothing has changed as far as this connection is concerned
    }

    stoppedReceiving_ = error;

    if (const char *sendError = stoppedSending()) {
        debugs(33, 3, HERE << "closing because also stopped sending: " << sendError);
        comm_close(fd);
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

// initialize dechunking state
void
ConnStateData::startDechunkingRequest(HttpParser *hp)
{
    debugs(33, 5, HERE << "start dechunking at " << HttpParserRequestLen(hp));
    assert(in.dechunkingState == chunkUnknown);
    assert(!in.bodyParser);
    in.bodyParser = new ChunkedCodingParser;
    in.chunkedSeen = HttpParserRequestLen(hp); // skip headers when dechunking
    in.chunked.init();  // TODO: should we have a smaller-than-default limit?
    in.dechunked.init();
    in.dechunkingState = chunkParsing;
}

// put parsed content into input buffer and clean up
void
ConnStateData::finishDechunkingRequest(HttpParser *hp)
{
    debugs(33, 5, HERE << "finish dechunking; content: " << in.dechunked.contentSize());

    assert(in.dechunkingState == chunkReady);

    const mb_size_t headerSize = HttpParserRequestLen(hp);

    // dechunking cannot make data bigger
    assert(headerSize + in.dechunked.contentSize() + in.chunked.contentSize()
           <= static_cast<mb_size_t>(in.notYetUsed));
    assert(in.notYetUsed <= in.allocatedSize);

    // copy dechunked content
    char *end = in.buf + headerSize;
    xmemmove(end, in.dechunked.content(), in.dechunked.contentSize());
    end += in.dechunked.contentSize();

    // copy post-chunks leftovers, if any, caused by request pipelining?
    if (in.chunked.contentSize()) {
        xmemmove(end, in.chunked.content(), in.chunked.contentSize());
        end += in.chunked.contentSize();
    }

    in.notYetUsed = end - in.buf;

    cleanDechunkingRequest();
}

/// cleanup dechunking state, get ready for the next request
void
ConnStateData::cleanDechunkingRequest()
{
    if (in.dechunkingState > chunkNone) {
        delete in.bodyParser;
        in.bodyParser = NULL;
        in.chunked.clean();
        in.dechunked.clean();
    }
    in.dechunkingState = chunkUnknown;
}

// parse newly read request chunks and buffer them for finishDechunkingRequest
// returns true iff needs more data
bool
ConnStateData::parseRequestChunks(HttpParser *)
{
    debugs(33,5, HERE << "parsing chunked request body at " <<
           in.chunkedSeen << " < " << in.notYetUsed);
    assert(in.bodyParser);
    assert(in.dechunkingState == chunkParsing);

    assert(in.chunkedSeen <= in.notYetUsed);
    const mb_size_t fresh = in.notYetUsed - in.chunkedSeen;

    // be safe: count some chunked coding metadata towards the total body size
    if (fresh + in.dechunked.contentSize() > Config.maxChunkedRequestBodySize) {
        debugs(33,3, HERE << "chunked body (" << fresh << " + " <<
               in.dechunked.contentSize() << " may exceed " <<
               "chunked_request_body_max_size=" <<
               Config.maxChunkedRequestBodySize);
        in.dechunkingState = chunkError;
        return false;
    }

    if (fresh > in.chunked.potentialSpaceSize()) {
        // should not happen if Config.maxChunkedRequestBodySize is reasonable
        debugs(33,1, HERE << "request_body_max_size exceeds chunked buffer " <<
               "size: " << fresh << " + " << in.chunked.contentSize() << " > " <<
               in.chunked.potentialSpaceSize() << " with " <<
               "chunked_request_body_max_size=" <<
               Config.maxChunkedRequestBodySize);
        in.dechunkingState = chunkError;
        return false;
    }
    in.chunked.append(in.buf + in.chunkedSeen, fresh);
    in.chunkedSeen += fresh;

    try { // the parser will throw on errors
        if (in.bodyParser->parse(&in.chunked, &in.dechunked))
            in.dechunkingState = chunkReady; // successfully parsed all chunks
        else
            return true; // need more, keep the same state
    } catch (...) {
        debugs(33,3, HERE << "chunk parsing error");
        in.dechunkingState = chunkError;
    }
    return false; // error, unsupported, or done
}

char *
ConnStateData::In::addressToReadInto() const
{
    return buf + notYetUsed;
}

ConnStateData::In::In() : bodyParser(NULL),
        buf (NULL), notYetUsed (0), allocatedSize (0),
        dechunkingState(ConnStateData::chunkUnknown)
{}

ConnStateData::In::~In()
{
    if (allocatedSize)
        memFreeBuf(allocatedSize, buf);
    if (bodyParser)
        delete bodyParser; // TODO: pool
}

/* This is a comm call normally scheduled by comm_close() */
void
ConnStateData::clientPinnedConnectionClosed(const CommCloseCbParams &io)
{
    pinning.fd = -1;
    if (pinning.peer) {
        cbdataReferenceDone(pinning.peer);
    }
    safe_free(pinning.host);
    /* NOTE: pinning.pinned should be kept. This combined with fd == -1 at the end of a request indicates that the host
     * connection has gone away */
}

void ConnStateData::pinConnection(int pinning_fd, HttpRequest *request, struct peer *aPeer, bool auth)
{
    fde *f;
    char desc[FD_DESC_SZ];

    if (pinning.fd == pinning_fd)
        return;
    else if (pinning.fd != -1)
        comm_close(pinning.fd);

    if (pinning.host)
        safe_free(pinning.host);

    pinning.fd = pinning_fd;
    pinning.host = xstrdup(request->GetHost());
    pinning.port = request->port;
    pinning.pinned = true;
    if (pinning.peer)
        cbdataReferenceDone(pinning.peer);
    if (aPeer)
        pinning.peer = cbdataReference(aPeer);
    pinning.auth = auth;
    f = &fd_table[fd];
    snprintf(desc, FD_DESC_SZ, "%s pinned connection for %s:%d (%d)",
             (auth || !aPeer) ? request->GetHost() : aPeer->name, f->ipaddr, (int) f->remote_port, fd);
    fd_note(pinning_fd, desc);

    typedef CommCbMemFunT<ConnStateData, CommCloseCbParams> Dialer;
    pinning.closeHandler = JobCallback(33, 5,
                                       Dialer, this, ConnStateData::clientPinnedConnectionClosed);
    comm_add_close_handler(pinning_fd, pinning.closeHandler);

}

int ConnStateData::validatePinnedConnection(HttpRequest *request, const struct peer *aPeer)
{
    bool valid = true;
    if (pinning.fd < 0)
        return -1;

    if (pinning.auth && request && strcasecmp(pinning.host, request->GetHost()) != 0) {
        valid = false;
    }
    if (request && pinning.port != request->port) {
        valid = false;
    }
