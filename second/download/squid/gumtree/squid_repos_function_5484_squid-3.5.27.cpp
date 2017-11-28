static void
ftpSendUser(Ftp::Gateway * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendUser"))
        return;

    if (ftpState->proxy_host != NULL)
        snprintf(cbuf, CTRL_BUFLEN, "USER %s@%s\r\n",
                 ftpState->user,
                 ftpState->request->GetHost());
    else
        snprintf(cbuf, CTRL_BUFLEN, "USER %s\r\n", ftpState->user);

    ftpState->writeCommand(cbuf);

    ftpState->state = Ftp::Client::SENT_USER;
}