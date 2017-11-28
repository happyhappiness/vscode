static void
ftpSendQuit(Ftp::Gateway * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendQuit"))
        return;

    snprintf(cbuf, CTRL_BUFLEN, "QUIT\r\n");
    ftpState->writeCommand(cbuf);
    ftpState->state = Ftp::Client::SENT_QUIT;
}