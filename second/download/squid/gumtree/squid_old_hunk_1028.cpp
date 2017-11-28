    debugs(85,3, HERE << "ICAP REQMOD callout failed, responding with error");

    clientStreamNode *node = (clientStreamNode *)client_stream.tail->prev->data;
    clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
    assert(repContext);

    // The original author of the code also wanted to pass an errno to
    // setReplyToError, but it seems unlikely that the errno reflects the
    // true cause of the error at this point, so I did not pass it.
    if (calloutContext) {
        Ip::Address noAddr;
        noAddr.setNoAddr();
        ConnStateData * c = getConn();
        calloutContext->error = clientBuildError(ERR_ICAP_FAILURE, Http::scInternalServerError,
                                NULL,
                                c != NULL ? c->clientConnection->remote : noAddr,
                                request
                                                );
#if USE_AUTH
        calloutContext->error->auth_user_request =
            c != NULL && c->getAuth() != NULL ? c->getAuth() : request->auth_user_request;
#endif
        calloutContext->error->detailError(errDetail);
        calloutContext->readNextRequest = true;
        if (c != NULL)
            c->expectNoForwarding();
        doCallouts();
    }
    //else if(calloutContext == NULL) is it possible?
}

void
ClientHttpRequest::callException(const std::exception &ex)
{
    const Comm::ConnectionPointer clientConn = getConn() ? getConn()->clientConnection : NULL;
    if (Comm::IsConnOpen(clientConn)) {
        debugs(85, 3, "closing after exception: " << ex.what());
        clientConn->close(); // initiate orderly top-to-bottom cleanup
        return;
    }

    debugs(85, DBG_IMPORTANT, "ClientHttpRequest exception without connection. Ignoring " << ex.what());
    // XXX: Normally, we mustStop() but we cannot do that here because it is
    // likely to leave Http::Stream and ConnStateData with a dangling http
    // pointer. See r13480 or XXX in Http::Stream class description.
}

#endif

