void
TunnelStateData::handleConnectResponse(const size_t chunkSize)
{
    assert(waitingForConnectResponse());

    // Ideally, client and server should use MemBuf or better, but current code
    // never accumulates more than one read when shoveling data (XXX) so it does
    // not need to deal with MemBuf complexity. To keep it simple, we use a
    // dedicated MemBuf for accumulating CONNECT responses. TODO: When shoveling
    // is optimized, reuse server.buf for CONNEC response accumulation instead.

    /* mimic the basic parts of HttpStateData::processReplyHeader() */
    HttpReply rep;
    Http::StatusCode parseErr = Http::scNone;
    const bool eof = !chunkSize;
    connectRespBuf->terminate(); // HttpMsg::parse requires terminated string
    const bool parsed = rep.parse(connectRespBuf->content(), connectRespBuf->contentSize(), eof, &parseErr);
    if (!parsed) {
        if (parseErr > 0) { // unrecoverable parsing error
            informUserOfPeerError("malformed CONNECT response from peer", 0);
            return;
        }

        // need more data
        assert(!eof);
        assert(!parseErr);

        if (!connectRespBuf->hasSpace()) {
            informUserOfPeerError("huge CONNECT response from peer", 0);
            return;
        }

        // keep reading
        readConnectResponse();
        return;
    }

    // CONNECT response was successfully parsed
    *status_ptr = rep.sline.status();

    // we need to relay the 401/407 responses when login=PASS(THRU)
    const CachePeer *peer = server.conn->getPeer();
    const char *pwd = (peer ? peer->login : nullptr);
    const bool relay = pwd && (strcmp(pwd, "PASS") == 0 || strcmp(pwd, "PASSTHRU") == 0) &&
                       (*status_ptr == Http::scProxyAuthenticationRequired ||
                        *status_ptr == Http::scUnauthorized);

    // bail if we did not get an HTTP 200 (Connection Established) response
    if (rep.sline.status() != Http::scOkay) {
        // if we ever decide to reuse the peer connection, we must extract the error response first
        informUserOfPeerError("unsupported CONNECT response status code", (relay ? rep.hdr_sz : 0));
        return;
    }

    if (rep.hdr_sz < connectRespBuf->contentSize()) {
        // preserve bytes that the server already sent after the CONNECT response
        server.len = connectRespBuf->contentSize() - rep.hdr_sz;
        memcpy(server.buf, connectRespBuf->content()+rep.hdr_sz, server.len);
    } else {
        // reset; delay pools were using this field to throttle CONNECT response
        server.len = 0;
    }

    delete connectRespBuf;
    connectRespBuf = NULL;
    connectExchangeCheckpoint();
}