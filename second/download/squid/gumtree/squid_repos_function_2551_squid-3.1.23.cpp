static void
ftpSendSize(FtpStateData * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendSize"))
        return;

    /* Only send SIZE for binary transfers. The returned size
     * is useless on ASCII transfers */

    if (ftpState->flags.binary) {
        assert(ftpState->filepath != NULL);
        assert(*ftpState->filepath != '\0');
        snprintf(cbuf, 1024, "SIZE %s\r\n", ftpState->filepath);
        ftpState->writeCommand(cbuf);
        ftpState->state = SENT_SIZE;
    } else
        /* Skip to next state no non-binary transfers */
        ftpSendPassive(ftpState);
}