static void
ftpSendRest(FtpStateData * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendRest"))
        return;

    debugs(9, 3, HERE);

    snprintf(cbuf, 1024, "REST %" PRId64 "\r\n", ftpState->restart_offset);
    ftpState->writeCommand(cbuf);
    ftpState->state = SENT_REST;
}