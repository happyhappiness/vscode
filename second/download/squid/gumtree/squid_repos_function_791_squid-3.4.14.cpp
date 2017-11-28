void
ClientHttpRequest::handleAdaptedHeader(HttpMsg *msg)
{
    assert(msg);

    if (HttpRequest *new_req = dynamic_cast<HttpRequest*>(msg)) {
        /*
         * Replace the old request with the new request.
         */
        HTTPMSGUNLOCK(request);
        request = new_req;
        HTTPMSGLOCK(request);

        // update the new message to flag whether URL re-writing was done on it
        if (strcmp(urlCanonical(request),uri) != 0)
            request->flags.redirected = 1;

        /*
         * Store the new URI for logging
         */
        xfree(uri);
        uri = xstrdup(urlCanonical(request));
        setLogUri(this, urlCanonicalClean(request));
        assert(request->method.id());
    } else if (HttpReply *new_rep = dynamic_cast<HttpReply*>(msg)) {
        debugs(85,3,HERE << "REQMOD reply is HTTP reply");

        // subscribe to receive reply body
        if (new_rep->body_pipe != NULL) {
            adaptedBodySource = new_rep->body_pipe;
            int consumer_ok = adaptedBodySource->setConsumerIfNotLate(this);
            assert(consumer_ok);
        }

        clientStreamNode *node = (clientStreamNode *)client_stream.tail->prev->data;
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert(repContext);
        repContext->createStoreEntry(request->method, request->flags);

        EBIT_CLR(storeEntry()->flags, ENTRY_FWD_HDR_WAIT);
        request_satisfaction_mode = true;
        request_satisfaction_offset = 0;
        storeEntry()->replaceHttpReply(new_rep);
        storeEntry()->timestampsSet();

        if (!adaptedBodySource) // no body
            storeEntry()->complete();
        clientGetMoreData(node, this);
    }

    // we are done with getting headers (but may be receiving body)
    clearAdaptation(virginHeadSource);

    if (!request_satisfaction_mode)
        doCallouts();
}