static void
ftpSendNlst(Ftp::Gateway * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendNlst"))
        return;

    debugs(9, 3, HERE);

    ftpState->flags.tried_nlst = 1;

    if (ftpState->filepath) {
        snprintf(cbuf, CTRL_BUFLEN, "NLST %s\r\n", ftpState->filepath);
    } else {
        snprintf(cbuf, CTRL_BUFLEN, "NLST\r\n");
    }

    ftpState->writeCommand(cbuf);
    ftpState->state = Ftp::Client::SENT_NLST;
}