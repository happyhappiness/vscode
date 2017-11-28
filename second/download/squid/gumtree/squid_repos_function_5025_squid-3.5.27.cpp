bool
Ftp::Server::writeControlMsgAndCall(ClientSocketContext *context, HttpReply *reply, AsyncCall::Pointer &call)
{
    // the caller guarantees that we are dealing with the current context only
    // the caller should also make sure reply->header.has(HDR_FTP_STATUS)
    writeForwardedReplyAndCall(reply, call);
    return true;
}