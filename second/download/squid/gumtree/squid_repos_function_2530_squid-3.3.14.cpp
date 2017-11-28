static void
ftpReadPass(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE << "code=" << code);

    if (code == 230) {
        ftpSendType(ftpState);
    } else {
        ftpState->loginFailed();
    }
}