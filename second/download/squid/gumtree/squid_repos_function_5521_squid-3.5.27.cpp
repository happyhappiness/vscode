static void
ftpSendRetr(Ftp::Gateway * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendRetr"))
        return;

    debugs(9, 3, HERE);

    assert(ftpState->filepath != NULL);
    snprintf(cbuf, CTRL_BUFLEN, "RETR %s\r\n", ftpState->filepath);
    ftpState->writeCommand(cbuf);
    ftpState->state = Ftp::Client::SENT_RETR;
}