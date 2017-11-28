static void
ftpReadMkdir(Ftp::Gateway * ftpState)
{
    char *path = ftpState->filepath;
    int code = ftpState->ctrl.replycode;

    debugs(9, 3, HERE << "path " << path << ", code " << code);

    if (code == 257) {      /* success */
        ftpSendCwd(ftpState);
    } else if (code == 550) {   /* dir exists */

        if (ftpState->flags.put_mkdir) {
            ftpState->flags.put_mkdir = 1;
            ftpSendCwd(ftpState);
        } else
            ftpSendReply(ftpState);
    } else
        ftpSendReply(ftpState);
}