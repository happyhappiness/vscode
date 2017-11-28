static void
ftpReadRetr(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code == 125 || (code == 150 && Comm::IsConnOpen(ftpState->data.conn))) {
        /* Begin data transfer */
        debugs(9, 3, HERE << "begin data transfer from " << ftpState->data.conn->remote << " (" << ftpState->data.conn->local << ")");
        ftpState->switchTimeoutToDataChannel();
        ftpState->maybeReadVirginBody();
        ftpState->state = READING_DATA;
    } else if (code == 150) {
        /* Accept data channel */
        ftpState->listenForDataChannel(ftpState->data.conn, ftpState->data.host);
    } else if (code >= 300) {
        if (!ftpState->flags.try_slash_hack) {
            /* Try this as a directory missing trailing slash... */
            ftpState->hackShortcut(ftpSendCwd);
        } else {
            ftpFail(ftpState);
        }
    } else {
        ftpFail(ftpState);
    }
}