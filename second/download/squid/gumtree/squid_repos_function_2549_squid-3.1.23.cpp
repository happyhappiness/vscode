static void
ftpSendMdtm(FtpStateData * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendMdtm"))
        return;

    assert(*ftpState->filepath != '\0');
    snprintf(cbuf, 1024, "MDTM %s\r\n", ftpState->filepath);
    ftpState->writeCommand(cbuf);
    ftpState->state = SENT_MDTM;
}