static void
ftpSendCwd(Ftp::Gateway * ftpState)
{
    char *path = NULL;

    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendCwd"))
        return;

    debugs(9, 3, HERE);

    path = ftpState->filepath;

    if (!strcmp(path, "..") || !strcmp(path, "/")) {
        ftpState->flags.no_dotdot = 1;
    } else {
        ftpState->flags.no_dotdot = 0;
    }

    snprintf(cbuf, CTRL_BUFLEN, "CWD %s\r\n", path);

    ftpState->writeCommand(cbuf);

    ftpState->state = Ftp::Client::SENT_CWD;
}