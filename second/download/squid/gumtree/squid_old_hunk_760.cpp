            conn->quitAfterError(request.getRaw());
            repContext->setReplyToError(ERR_TOO_BIG,
                                        Http::scPayloadTooLarge, Http::METHOD_NONE, NULL,
                                        conn->clientConnection->remote, http->request, NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            goto finish;
        }

        // We may stop producing, comm_close, and/or call setReplyToError()
        // below, so quit on errors to avoid http->doCallouts()
        if (!conn->handleRequestBodyData())
            goto finish;

        if (!request->body_pipe->productionEnded()) {
            debugs(33, 5, HERE << "need more request body");
            context->mayUseConnection(true);
            assert(conn->flags.readMore);
        }
    }

    http->calloutContext = new ClientRequestContext(http);

    http->doCallouts();

finish:
    if (!notedUseOfBuffer)
        connNoteUseOfBuffer(conn, http->req_sz);

    /*
     * DPW 2007-05-18
     * Moved the TCP_RESET feature from clientReplyContext::sendMoreData
     * to here because calling comm_reset_close() causes http to
     * be freed and the above connNoteUseOfBuffer() would hit an
     * assertion, not to mention that we were accessing freed memory.
     */
    if (request != NULL && request->flags.resetTcp && Comm::IsConnOpen(conn->clientConnection)) {
        debugs(33, 3, HERE << "Sending TCP RST on " << conn->clientConnection);
        conn->flags.readMore = false;
        comm_reset_close(conn->clientConnection);
    }
}

static void
connStripBufferWhitespace (ConnStateData * conn)
{
    while (conn->in.notYetUsed > 0 && xisspace(conn->in.buf[0])) {
        memmove(conn->in.buf, conn->in.buf + 1, conn->in.notYetUsed - 1);
        -- conn->in.notYetUsed;
    }
}

/**
 * Limit the number of concurrent requests.
 * \return true  when there are available position(s) in the pipeline queue for another request.
 * \return false when the pipeline queue is full or disabled.
 */
bool
ConnStateData::concurrentRequestQueueFilled() const
{
    const int existingRequestCount = getConcurrentRequestCount();

    // default to the configured pipeline size.
    // add 1 because the head of pipeline is counted in concurrent requests and not prefetch queue
    const int concurrentRequestLimit = Config.pipeline_max_prefetch + 1;

    // when queue filled already we cant add more.
    if (existingRequestCount >= concurrentRequestLimit) {
        debugs(33, 3, clientConnection << " max concurrent requests reached (" << concurrentRequestLimit << ")");
        debugs(33, 5, clientConnection << " deferring new request until one is done");
        return true;
    }

    return false;
}

/**
 * Attempt to parse one or more requests from the input buffer.
 * If a request is successfully parsed, even if the next request
 * is only partially parsed, it will return TRUE.
 */
bool
ConnStateData::clientParseRequests()
{
    HttpRequestMethod method;
    bool parsed_req = false;

    debugs(33, 5, HERE << clientConnection << ": attempting to parse");

    // Loop while we have read bytes that are not needed for producing the body
    // On errors, bodyPipe may become nil, but readMore will be cleared
    while (in.notYetUsed > 0 && !bodyPipe && flags.readMore) {
        connStripBufferWhitespace(this);

        /* Don't try to parse if the buffer is empty */
        if (in.notYetUsed == 0)
            break;

        /* Limit the number of concurrent requests */
        if (concurrentRequestQueueFilled())
            break;

        /* Should not be needed anymore */
        /* Terminate the string */
        in.buf[in.notYetUsed] = '\0';

        /* Begin the parsing */
        PROF_start(parseHttpRequest);
        HttpParserInit(&parser_, in.buf, in.notYetUsed);

        /* Process request */
        Http::ProtocolVersion http_ver;
        ClientSocketContext *context = parseHttpRequest(this, &parser_, &method, &http_ver);
        PROF_stop(parseHttpRequest);

        /* partial or incomplete request */
        if (!context) {
            // TODO: why parseHttpRequest can just return parseHttpRequestAbort
            // (which becomes context) but checkHeaderLimits cannot?
            checkHeaderLimits();
            break;
        }

        /* status -1 or 1 */
        if (context) {
            debugs(33, 5, HERE << clientConnection << ": parsed a request");
            AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "clientLifetimeTimeout",
                                             CommTimeoutCbPtrFun(clientLifetimeTimeout, context->http));
            commSetConnTimeout(clientConnection, Config.Timeout.lifetime, timeoutCall);

            clientProcessRequest(this, &parser_, context, method, http_ver);

            parsed_req = true; // XXX: do we really need to parse everything right NOW ?

            if (context->mayUseConnection()) {
                debugs(33, 3, HERE << "Not parsing new requests, as this request may need the connection");
                break;
            }
        }
    }

    /* XXX where to 'finish' the parsing pass? */
    return parsed_req;
}

void
ConnStateData::clientReadRequest(const CommIoCbParams &io)
{
    debugs(33,5,HERE << io.conn << " size " << io.size);
    Must(reading());
    reader = NULL;

    /* Bail out quickly on COMM_ERR_CLOSING - close handlers will tidy up */

    if (io.flag == COMM_ERR_CLOSING) {
        debugs(33,5, HERE << io.conn << " closing Bailout.");
        return;
    }

    assert(Comm::IsConnOpen(clientConnection));
    assert(io.conn->fd == clientConnection->fd);

    /*
     * Don't reset the timeout value here.  The timeout value will be
     * set to Config.Timeout.request by httpAccept() and
     * clientWriteComplete(), and should apply to the request as a
     * whole, not individual read() calls.  Plus, it breaks our
     * lame half-close detection
     */
    if (connReadWasError(io.flag, io.size, io.xerrno)) {
        notifyAllContexts(io.xerrno);
        io.conn->close();
        return;
    }

    if (io.flag == COMM_OK) {
        if (io.size > 0) {
            kb_incr(&(statCounter.client_http.kbytes_in), io.size);

            // may comm_close or setReplyToError
            if (!handleReadData(io.buf, io.size))
                return;

        } else if (io.size == 0) {
            debugs(33, 5, HERE << io.conn << " closed?");

            if (connFinishedWithConn(io.size)) {
                clientConnection->close();
                return;
            }

            /* It might be half-closed, we can't tell */
            fd_table[io.conn->fd].flags.socket_eof = true;

            commMarkHalfClosed(io.conn->fd);

            fd_note(io.conn->fd, "half-closed");

            /* There is one more close check at the end, to detect aborted
             * (partial) requests. At this point we can't tell if the request
             * is partial.
             */
            /* Continue to process previously read data */
        }
    }

    /* Process next request */
    if (getConcurrentRequestCount() == 0)
        fd_note(io.fd, "Reading next request");

