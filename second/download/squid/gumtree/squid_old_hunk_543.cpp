    return newContext;
}

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
