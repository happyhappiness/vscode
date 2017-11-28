static void
ftpSendStor(FtpStateData * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendStor"))
        return;

    debugs(9, 3, HERE);

    if (ftpState->filepath != NULL) {
        /* Plain file upload */
        snprintf(cbuf, CTRL_BUFLEN, "STOR %s\r\n", ftpState->filepath);
        ftpState->writeCommand(cbuf);
        ftpState->state = SENT_STOR;
    } else if (ftpState->request->header.getInt64(HDR_CONTENT_LENGTH) > 0) {
        /* File upload without a filename. use STOU to generate one */
        snprintf(cbuf, CTRL_BUFLEN, "STOU\r\n");
        ftpState->writeCommand(cbuf);
        ftpState->state = SENT_STOR;
    } else {
        /* No file to transfer. Only create directories if needed */
        ftpSendReply(ftpState);
    }
}