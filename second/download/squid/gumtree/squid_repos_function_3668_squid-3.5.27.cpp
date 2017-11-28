void httpsSslBumpStep2AccessCheckDone(allow_t answer, void *data)
{
    ConnStateData *connState = (ConnStateData *) data;

    // if the connection is closed or closing, just return.
    if (!connState->isOpen())
        return;

    debugs(33, 5, "Answer: " << answer << " kind:" << answer.kind);
    assert(connState->serverBump());
    Ssl::BumpMode bumpAction;
    if (answer == ACCESS_ALLOWED) {
        bumpAction = (Ssl::BumpMode)answer.kind;
    } else
        bumpAction = Ssl::bumpSplice;

    connState->serverBump()->act.step2 = bumpAction;
    connState->sslBumpMode = bumpAction;

    if (bumpAction == Ssl::bumpTerminate) {
        connState->clientConnection->close();
    } else if (bumpAction != Ssl::bumpSplice) {
        connState->startPeekAndSpliceDone();
    } else {
        //Normally we can splice here, because we just got client hello message
        SSL *ssl = fd_table[connState->clientConnection->fd].ssl;
        BIO *b = SSL_get_rbio(ssl);
        Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(b->ptr);
        MemBuf const &rbuf = bio->rBufData();
        debugs(83,5, "Bio for  " << connState->clientConnection << " read " << rbuf.contentSize() << " helo bytes");
        // Do splice:
        fd_table[connState->clientConnection->fd].read_method = &default_read_method;
        fd_table[connState->clientConnection->fd].write_method = &default_write_method;

        ClientSocketContext::Pointer context = connState->getCurrentContext();
        Must(context != NULL);
        if (connState->transparent()) {
            // If we are going to fake the second CONNECT, clear the first one.
            context->connIsFinished();

            // fake a CONNECT request to force connState to tunnel
            // XXX: copy from MemBuf reallocates, not a regression since old code did too
            SBuf temp;
            temp.append(rbuf.content(), rbuf.contentSize());
            connState->fakeAConnectRequest("intercepted TLS spliced", temp);
        } else {
            // in.buf still has the "CONNECT ..." request data, reset it to SSL hello message
            connState->in.buf.append(rbuf.content(), rbuf.contentSize());
            ClientHttpRequest *http = context->http;
            tunnelStart(http);
        }
    }
}