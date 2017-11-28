static void
ftpReadPORT(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code != 200) {
        /* Fall back on using the same port as the control connection */
        debugs(9, 3, "PORT not supported by remote end");
        ftpOpenListenSocket(ftpState, 1);
    }

    ftpRestOrList(ftpState);
}