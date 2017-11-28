void
Ftp::Server::writeForwardedReplyAndCall(const HttpReply *reply, AsyncCall::Pointer &call)
{
    assert(reply != NULL);
    const HttpHeader &header = reply->header;

    // without status, the caller must use the writeForwardedForeign() path
    Must(header.has(HDR_FTP_STATUS));
    Must(header.has(HDR_FTP_REASON));
    const int scode = header.getInt(HDR_FTP_STATUS);
    debugs(33, 7, "scode: " << scode);

    // Status 125 or 150 implies upload or data request, but we still check
    // the state in case the server is buggy.
    if ((scode == 125 || scode == 150) &&
            (master->serverState == fssHandleUploadRequest ||
             master->serverState == fssHandleDataRequest)) {
        if (checkDataConnPost()) {
            // If the data connection is ready, start reading data (here)
            // and forward the response to client (further below).
            debugs(33, 7, "data connection established, start data transfer");
            if (master->serverState == fssHandleUploadRequest)
                maybeReadUploadData();
        } else {
            // If we are waiting to accept the data connection, keep waiting.
            if (Comm::IsConnOpen(dataListenConn)) {
                debugs(33, 7, "wait for the client to establish a data connection");
                onDataAcceptCall = call;
                // TODO: Add connect timeout for passive connections listener?
                // TODO: Remember server response so that we can forward it?
            } else {
                // Either the connection was establised and closed after the
                // data was transferred OR we failed to establish an active
                // data connection and already sent the error to the client.
                // In either case, there is nothing more to do.
                debugs(33, 7, "done with data OR active connection failed");
            }
            return;
        }
    }

    MemBuf mb;
    mb.init();
    Ftp::PrintReply(mb, reply);

    debugs(9, 2, "FTP Client " << clientConnection);
    debugs(9, 2, "FTP Client REPLY:\n---------\n" << mb.buf <<
           "\n----------");

    Comm::Write(clientConnection, &mb, call);
}