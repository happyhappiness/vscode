static void
ftpSendMkdir(Ftp::Gateway * ftpState)
{
    char *path = NULL;

    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendMkdir"))
        return;

    path = ftpState->filepath;
    debugs(9, 3, HERE << "with path=" << path);
    snprintf(cbuf, CTRL_BUFLEN, "MKD %s\r\n", path);
    ftpState->writeCommand(cbuf);
    ftpState->state = Ftp::Client::SENT_MKDIR;
}