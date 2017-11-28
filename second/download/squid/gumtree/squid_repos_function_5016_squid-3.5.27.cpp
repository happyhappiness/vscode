void
Ftp::Server::handleDataReply(const HttpReply *reply, StoreIOBuffer data)
{
    if (reply != NULL && reply->sline.status() != Http::scOkay) {
        writeForwardedReply(reply);
        if (Comm::IsConnOpen(dataConn)) {
            debugs(33, 3, "closing " << dataConn << " on KO reply");
            closeDataConnection();
        }
        return;
    }

    if (!dataConn) {
        // We got STREAM_COMPLETE (or error) and closed the client data conn.
        debugs(33, 3, "ignoring FTP srv data response after clt data closure");
        return;
    }

    if (!checkDataConnPost()) {
        writeCustomReply(425, "Data connection is not established.");
        closeDataConnection();
        return;
    }

    debugs(33, 7, data.length);

    if (data.length <= 0) {
        replyDataWritingCheckpoint(); // skip the actual write call
        return;
    }

    MemBuf mb;
    mb.init(data.length + 1, data.length + 1);
    mb.append(data.data, data.length);

    typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(33, 5, Dialer, this, Ftp::Server::wroteReplyData);
    Comm::Write(dataConn, &mb, call);

    getCurrentContext()->noteSentBodyBytes(data.length);
}