void
ClientHttpRequest::handleAdaptationFailure(int errDetail, bool bypassable)
{
    debugs(85,3, HERE << "handleAdaptationFailure(" << bypassable << ")");

    const bool usedStore = storeEntry() && !storeEntry()->isEmpty();
    const bool usedPipe = request->body_pipe != NULL &&
                          request->body_pipe->consumedSize() > 0;

    if (bypassable && !usedStore && !usedPipe) {
        debugs(85,3, HERE << "ICAP REQMOD callout failed, bypassing: " << calloutContext);
        if (calloutContext)
            doCallouts();
        return;
    }

    debugs(85,3, HERE << "ICAP REQMOD callout failed, responding with error");

    clientStreamNode *node = (clientStreamNode *)client_stream.tail->prev->data;
    clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
    assert(repContext);

    // The original author of the code also wanted to pass an errno to
    // setReplyToError, but it seems unlikely that the errno reflects the
    // true cause of the error at this point, so I did not pass it.
    if (calloutContext) {
        Ip::Address noAddr;
        noAddr.SetNoAddr();
        ConnStateData * c = getConn();
        calloutContext->error = clientBuildError(ERR_ICAP_FAILURE, HTTP_INTERNAL_SERVER_ERROR,
                                NULL,
                                c != NULL ? c->clientConnection->remote : noAddr,
                                request
                                                );
#if USE_AUTH
        calloutContext->error->auth_user_request =
            c != NULL && c->auth_user_request != NULL ? c->auth_user_request : request->auth_user_request;
#endif
        calloutContext->error->detailError(errDetail);
        calloutContext->readNextRequest = true;
        if (c != NULL)
            c->expectNoForwarding();
        doCallouts();
    }
    //else if(calloutContext == NULL) is it possible?
}