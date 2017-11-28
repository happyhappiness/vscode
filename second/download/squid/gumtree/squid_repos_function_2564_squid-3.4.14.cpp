static void
ftpSendType(FtpStateData * ftpState)
{
    const char *t;
    const char *filename;
    char mode;

    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendType"))
        return;

    /*
     * Ref section 3.2.2 of RFC 1738
     */
    mode = ftpState->typecode;

    switch (mode) {

    case 'D':
        mode = 'A';
        break;

    case 'A':

    case 'I':
        break;

    default:

        if (ftpState->flags.isdir) {
            mode = 'A';
        } else {
            t = ftpState->request->urlpath.rpos('/');
            filename = t ? t + 1 : ftpState->request->urlpath.termedBuf();
            mode = mimeGetTransferMode(filename);
        }

        break;
    }

    if (mode == 'I')
        ftpState->flags.binary = 1;
    else
        ftpState->flags.binary = 0;

    snprintf(cbuf, CTRL_BUFLEN, "TYPE %c\r\n", mode);

    ftpState->writeCommand(cbuf);

    ftpState->state = SENT_TYPE;
}