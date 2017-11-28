static void
ftpReadList(Ftp::Gateway * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code == 125 || (code == 150 && Comm::IsConnOpen(ftpState->data.conn))) {
        /* Begin data transfer */
        debugs(9, 3, HERE << "begin data transfer from " << ftpState->data.conn->remote << " (" << ftpState->data.conn->local << ")");
        ftpState->switchTimeoutToDataChannel();
        ftpState->maybeReadVirginBody();
        ftpState->state = Ftp::Client::READING_DATA;
        return;
    } else if (code == 150) {
        /* Accept data channel */
        debugs(9, 3, HERE << "accept data channel from " << ftpState->data.conn->remote << " (" << ftpState->data.conn->local << ")");
        ftpState->listenForDataChannel(ftpState->data.conn);
        return;
    } else if (!ftpState->flags.tried_nlst && code > 300) {
        ftpSendNlst(ftpState);
    } else {
        ftpFail(ftpState);
        return;
    }
}