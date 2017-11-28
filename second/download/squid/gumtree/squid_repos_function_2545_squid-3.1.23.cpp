static void
ftpSendMkdir(FtpStateData * ftpState)
{
    char *path = NULL;

    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendMkdir"))
        return;

    path = ftpState->filepath;
    debugs(9, 3, HERE << "with path=" << path);
    snprintf(cbuf, 1024, "MKD %s\r\n", path);
    ftpState->writeCommand(cbuf);
    ftpState->state = SENT_MKDIR;
}