static void
ftpReadRest(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);
    assert(ftpState->restart_offset > 0);

    if (code == 350) {
        ftpState->setCurrentOffset(ftpState->restart_offset);
        ftpSendRetr(ftpState);
    } else if (code > 0) {
        debugs(9, 3, HERE << "REST not supported");
        ftpState->flags.rest_supported = 0;
        ftpSendRetr(ftpState);
    } else {
        ftpFail(ftpState);
    }
}