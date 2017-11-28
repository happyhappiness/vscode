static void
ftpSendList(Ftp::Gateway * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendList"))
        return;

    debugs(9, 3, HERE);

    if (ftpState->filepath) {
        snprintf(cbuf, CTRL_BUFLEN, "LIST %s\r\n", ftpState->filepath);
    } else {
        snprintf(cbuf, CTRL_BUFLEN, "LIST\r\n");
    }

    ftpState->writeCommand(cbuf);
    ftpState->state = Ftp::Client::SENT_LIST;
}