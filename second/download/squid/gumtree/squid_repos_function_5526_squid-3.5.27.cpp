static void
ftpWriteTransferDone(Ftp::Gateway * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (!(code == 226 || code == 250)) {
        debugs(9, DBG_IMPORTANT, HERE << "Got code " << code << " after sending data");
        ftpState->failed(ERR_FTP_PUT_ERROR, 0);
        return;
    }

    ftpState->entry->timestampsSet();   /* XXX Is this needed? */
    ftpSendReply(ftpState);
}