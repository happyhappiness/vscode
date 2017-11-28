static void
ftpSendPass(Ftp::Gateway * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendPass"))
        return;

    snprintf(cbuf, CTRL_BUFLEN, "PASS %s\r\n", ftpState->password);
    ftpState->writeCommand(cbuf);
    ftpState->state = Ftp::Client::SENT_PASS;
}