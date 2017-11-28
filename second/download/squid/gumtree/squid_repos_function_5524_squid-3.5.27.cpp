static void
ftpReadTransferDone(Ftp::Gateway * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code == 226 || code == 250) {
        /* Connection closed; retrieval done. */
        if (ftpState->flags.listing) {
            ftpState->completedListing();
            /* QUIT operation handles sending the reply to client */
        }
        ftpSendQuit(ftpState);
    } else {            /* != 226 */
        debugs(9, DBG_IMPORTANT, HERE << "Got code " << code << " after reading data");
        ftpState->failed(ERR_FTP_FAILURE, 0);
        /* failed closes ctrl.conn and frees ftpState */
        return;
    }
}