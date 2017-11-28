static void
ftpSendMdtm(FtpStateData * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendMdtm"))
        return;

    assert(*ftpState->filepath != '\0');
    snprintf(cbuf, CTRL_BUFLEN, "MDTM %s\r\n", ftpState->filepath);
    ftpState->writeCommand(cbuf);
    ftpState->state = SENT_MDTM;
}