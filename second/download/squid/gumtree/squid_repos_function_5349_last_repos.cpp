static void
ftpSendType(Ftp::Gateway * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendType"))
        return;

    /*
     * Ref section 3.2.2 of RFC 1738
     */
    char mode = ftpState->typecode;

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
            auto t = ftpState->request->url.path().rfind('/');
            // XXX: performance regression, c_str() may reallocate
            SBuf filename = ftpState->request->url.path().substr(t != SBuf::npos ? t + 1 : 0);
            mode = mimeGetTransferMode(filename.c_str());
        }

        break;
    }

    if (mode == 'I')
        ftpState->flags.binary = 1;
    else
        ftpState->flags.binary = 0;

    snprintf(cbuf, CTRL_BUFLEN, "TYPE %c\r\n", mode);

    ftpState->writeCommand(cbuf);

    ftpState->state = Ftp::Client::SENT_TYPE;
}