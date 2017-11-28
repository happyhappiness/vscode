bool
ConnStateData::clientParseRequests()
{
    bool parsed_req = false;

    debugs(33, 5, HERE << clientConnection << ": attempting to parse");

    // Loop while we have read bytes that are not needed for producing the body
    // On errors, bodyPipe may become nil, but readMore will be cleared
    while (!in.buf.isEmpty() && !bodyPipe && flags.readMore) {
        connStripBufferWhitespace(this);

        /* Don't try to parse if the buffer is empty */
        if (in.buf.isEmpty())
            break;

        // Prohibit concurrent requests when using a pinned to-server connection
        // because our Client classes do not support request pipelining.
        if (pinning.pinned && !pinning.readHandler) {
            debugs(33, 3, clientConnection << " waits for busy " << pinning.serverConnection);
            break;
        }

        /* Limit the number of concurrent requests */
        if (concurrentRequestQueueFilled())
            break;

        // try to parse the PROXY protocol header magic bytes
        if (needProxyProtocolHeader_ && !parseProxyProtocolHeader())
            break;

        Http::ProtocolVersion http_ver;
        if (ClientSocketContext *context = parseOneRequest(http_ver)) {
            debugs(33, 5, clientConnection << ": done parsing a request");
            AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "clientLifetimeTimeout",
                                             CommTimeoutCbPtrFun(clientLifetimeTimeout, context->http));
            commSetConnTimeout(clientConnection, Config.Timeout.lifetime, timeoutCall);

            context->registerWithConn();

            processParsedRequest(context, http_ver);

            parsed_req = true; // XXX: do we really need to parse everything right NOW ?

            if (context->mayUseConnection()) {
                debugs(33, 3, HERE << "Not parsing new requests, as this request may need the connection");
                break;
            }
        } else {
            debugs(33, 5, clientConnection << ": not enough request data: " <<
                   in.buf.length() << " < " << Config.maxRequestHeaderSize);
            Must(in.buf.length() < Config.maxRequestHeaderSize);
            break;
        }
    }

    /* XXX where to 'finish' the parsing pass? */
    return parsed_req;
}