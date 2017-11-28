bool
Http::Server::writeControlMsgAndCall(ClientSocketContext *context, HttpReply *rep, AsyncCall::Pointer &call)
{
    // Ignore this late control message if we have started sending a
    // reply to the user already (e.g., after an error).
    if (context->reply) {
        debugs(11, 2, "drop 1xx made late by " << context->reply);
        return false;
    }

    // apply selected clientReplyContext::buildReplyHeader() mods
    // it is not clear what headers are required for control messages
    rep->header.removeHopByHopEntries();
    rep->header.putStr(HDR_CONNECTION, "keep-alive");
    httpHdrMangleList(&rep->header, getCurrentContext()->http->request, ROR_REPLY);

    MemBuf *mb = rep->pack();

    debugs(11, 2, "HTTP Client " << clientConnection);
    debugs(11, 2, "HTTP Client CONTROL MSG:\n---------\n" << mb->buf << "\n----------");

    Comm::Write(context->clientConnection, mb, call);

    delete mb;
    return true;
}