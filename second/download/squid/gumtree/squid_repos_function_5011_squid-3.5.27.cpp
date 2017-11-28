void
Ftp::Server::handleReply(HttpReply *reply, StoreIOBuffer data)
{
    // the caller guarantees that we are dealing with the current context only
    ClientSocketContext::Pointer context = getCurrentContext();
    assert(context != NULL);

    if (context->http && context->http->al != NULL &&
            !context->http->al->reply && reply) {
        context->http->al->reply = reply;
        HTTPMSGLOCK(context->http->al->reply);
    }

    static ReplyHandler handlers[] = {
        NULL, // fssBegin
        NULL, // fssConnected
        &Ftp::Server::handleFeatReply, // fssHandleFeat
        &Ftp::Server::handlePasvReply, // fssHandlePasv
        &Ftp::Server::handlePortReply, // fssHandlePort
        &Ftp::Server::handleDataReply, // fssHandleDataRequest
        &Ftp::Server::handleUploadReply, // fssHandleUploadRequest
        &Ftp::Server::handleEprtReply,// fssHandleEprt
        &Ftp::Server::handleEpsvReply,// fssHandleEpsv
        NULL, // fssHandleCwd
        NULL, // fssHandlePass
        NULL, // fssHandleCdup
        &Ftp::Server::handleErrorReply // fssError
    };
    try {
        const Server &server = dynamic_cast<const Ftp::Server&>(*context->getConn());
        if (const ReplyHandler handler = handlers[server.master->serverState])
            (this->*handler)(reply, data);
        else
            writeForwardedReply(reply);
    } catch (const std::exception &e) {
        callException(e);
        throw TexcHere(e.what());
    }
}