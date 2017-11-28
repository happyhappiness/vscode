void
ClientSocketContext::writeControlMsg(HttpControlMsg &msg)
{
    HttpReply *rep = msg.reply;
    Must(rep);

    // apply selected clientReplyContext::buildReplyHeader() mods
    // it is not clear what headers are required for control messages
    rep->header.removeHopByHopEntries();
    rep->header.putStr(HDR_CONNECTION, "keep-alive");
    httpHdrMangleList(&rep->header, http->request, ROR_REPLY);

    // remember the callback
    cbControlMsgSent = msg.cbSuccess;

    MemBuf *mb = rep->pack();

    debugs(11, 2, "HTTP Client " << clientConnection);
    debugs(11, 2, "HTTP Client CONTROL MSG:\n---------\n" << mb->buf << "\n----------");

    AsyncCall::Pointer call = commCbCall(33, 5, "ClientSocketContext::wroteControlMsg",
                                         CommIoCbPtrFun(&WroteControlMsg, this));
    Comm::Write(clientConnection, mb, call);

    delete mb;
}