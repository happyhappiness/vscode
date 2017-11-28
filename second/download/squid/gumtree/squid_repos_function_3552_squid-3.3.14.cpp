bool
ConnStateData::clientParseRequests()
{
    HttpRequestMethod method;
    bool parsed_req = false;
    HttpVersion http_ver;

    debugs(33, 5, HERE << clientConnection << ": attempting to parse");

    // Loop while we have read bytes that are not needed for producing the body
    // On errors, bodyPipe may become nil, but readMore will be cleared
    while (in.notYetUsed > 0 && !bodyPipe && flags.readMore) {
        connStripBufferWhitespace(this);

        /* Don't try to parse if the buffer is empty */
        if (in.notYetUsed == 0)
            break;

        /* Limit the number of concurrent requests to 2 */
        if (!connOkToAddRequest(this)) {
            break;
        }

        /* Should not be needed anymore */
        /* Terminate the string */
        in.buf[in.notYetUsed] = '\0';

        /* Begin the parsing */
        PROF_start(parseHttpRequest);
        HttpParserInit(&parser_, in.buf, in.notYetUsed);

        /* Process request */
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