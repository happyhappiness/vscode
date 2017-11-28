void
Http::One::Server::setReplyError(Http::StreamPointer &context, HttpRequest::Pointer &request, const HttpRequestMethod& method, err_type requestError, Http::StatusCode errStatusCode, const char *requestErrorBytes)
{
    quitAfterError(request.getRaw());
    if (!context->connRegistered()) {
        debugs(33, 2, "Client stream deregister it self, nothing to do");
        clientConnection->close();
        return;
    }
    clientStreamNode *node = context->getClientReplyContext();
    clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
    assert (repContext);

    repContext->setReplyToError(requestError, errStatusCode, method, context->http->uri, clientConnection->remote, nullptr, requestErrorBytes, nullptr);

    assert(context->http->out.offset == 0);
    context->pullData();
}