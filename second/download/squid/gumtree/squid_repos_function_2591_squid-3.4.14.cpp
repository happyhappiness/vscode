void FtpStateData::readStor()
{
    int code = ctrl.replycode;
    debugs(9, 3, HERE);

    if (code == 125 || (code == 150 && Comm::IsConnOpen(data.conn))) {
        if (!originalRequest()->body_pipe) {
            debugs(9, 3, "zero-size STOR?");
            state = WRITING_DATA; // make ftpWriteTransferDone() responsible
            dataComplete(); // XXX: keep in sync with doneSendingRequestBody()
            return;
        }

        if (!startRequestBodyFlow()) { // register to receive body data
            ftpFail(this);
            return;
        }

        /* When client status is 125, or 150 and the data connection is open, Begin data transfer. */
        debugs(9, 3, HERE << "starting data transfer");
        switchTimeoutToDataChannel();
        sendMoreRequestBody();
        fwd->dontRetry(true); // dont permit re-trying if the body was sent.
        state = WRITING_DATA;
        debugs(9, 3, HERE << "writing data channel");
    } else if (code == 150) {
        /* When client code is 150 with no data channel, Accept data channel. */
        debugs(9, 3, "ftpReadStor: accepting data channel");
        listenForDataChannel(data.conn, data.host);
    } else {
        debugs(9, DBG_IMPORTANT, HERE << "Unexpected reply code "<< std::setfill('0') << std::setw(3) << code);
        ftpFail(this);
    }
}