void
Ftp::Server::writeForwardedReply(const HttpReply *reply)
{
    Must(reply);

    if (waitingForOrigin) {
        Must(delayedReply == NULL);
        delayedReply = reply;
        return;
    }

    const HttpHeader &header = reply->header;
    // adaptation and forwarding errors lack HDR_FTP_STATUS
    if (!header.has(HDR_FTP_STATUS)) {
        writeForwardedForeign(reply); // will get to Ftp::Server::wroteReply
        return;
    }

    typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(33, 5, Dialer, this, Ftp::Server::wroteReply);
    writeForwardedReplyAndCall(reply, call);
}