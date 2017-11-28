static void
ftpSendPass(FtpStateData * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendPass"))
        return;

    snprintf(cbuf, CTRL_BUFLEN, "PASS %s\r\n", ftpState->password);
    ftpState->writeCommand(cbuf);
    ftpState->state = SENT_PASS;
}