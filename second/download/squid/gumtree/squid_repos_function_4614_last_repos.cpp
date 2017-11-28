void
Ftp::Server::acceptDataConnection(const CommAcceptCbParams &params)
{
    if (params.flag != Comm::OK) {
        // Its possible the call was still queued when the client disconnected
        debugs(33, 2, dataListenConn << ": accept "
               "failure: " << xstrerr(params.xerrno));
        return;
    }

    debugs(33, 4, "accepted " << params.conn);
    fd_note(params.conn->fd, "passive client ftp data");
    ++incoming_sockets_accepted;

    if (!clientConnection) {
        debugs(33, 5, "late data connection?");
        closeDataConnection(); // in case we are still listening
        params.conn->close();
    } else if (params.conn->remote != clientConnection->remote) {
        debugs(33, 2, "rogue data conn? ctrl: " << clientConnection->remote);
        params.conn->close();
        // Some FTP servers close control connection here, but it may make
        // things worse from DoS p.o.v. and no better from data stealing p.o.v.
    } else {
        closeDataConnection();
        dataConn = params.conn;
        uploadAvailSize = 0;
        debugs(33, 7, "ready for data");
        if (onDataAcceptCall != NULL) {
            AsyncCall::Pointer call = onDataAcceptCall;
            onDataAcceptCall = NULL;
            // If we got an upload request, start reading data from the client.
            if (master->serverState == fssHandleUploadRequest)
                maybeReadUploadData();
            else
                Must(master->serverState == fssHandleDataRequest);
            MemBuf mb;
            mb.init();
            mb.appendf("150 Data connection opened.\r\n");
            Comm::Write(clientConnection, &mb, call);
        }
    }
}