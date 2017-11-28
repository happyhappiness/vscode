static void
ftpReadEPRT(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code != 200) {
        /* Failover to attempting old PORT command. */
        debugs(9, 3, "EPRT not supported by remote end");
        ftpSendPORT(ftpState);
        return;
    }

    ftpRestOrList(ftpState);
}