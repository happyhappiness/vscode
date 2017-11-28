void
ConnStateData::abortChunkedRequestBody(const err_type error)
{
    finishDechunkingRequest(false);

    // XXX: The code below works if we fail during initial request parsing,
    // but if we fail when the server connection is used already, the server may send
    // us its response too, causing various assertions. How to prevent that?
#if WE_KNOW_HOW_TO_SEND_ERRORS
    ClientSocketContext::Pointer context = getCurrentContext();
    if (context != NULL && !context->http->out.offset) { // output nothing yet
        clientStreamNode *node = context->getClientReplyContext();
        clientReplyContext *repContext = dynamic_cast<clientReplyContext*>(node->data.getRaw());
        assert(repContext);
        const Http::StatusCode scode = (error == ERR_TOO_BIG) ?
                                       Http::scPayloadTooLarge : HTTP_BAD_REQUEST;
        repContext->setReplyToError(error, scode,
                                    repContext->http->request->method,
                                    repContext->http->uri,
                                    CachePeer,
                                    repContext->http->request,
                                    in.buf, NULL);
        context->pullData();
    } else {
        // close or otherwise we may get stuck as nobody will notice the error?
        comm_reset_close(clientConnection);
    }
#else
    debugs(33, 3, HERE << "aborting chunked request without error " << error);
    comm_reset_close(clientConnection);
#endif
    flags.readMore = false;
}