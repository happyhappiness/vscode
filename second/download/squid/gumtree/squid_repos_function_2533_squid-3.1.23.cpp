static void
ftpReadWelcome(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (ftpState->flags.pasv_only)
        ftpState->login_att++;

    /* Dont retry if the FTP server accepted the connection */
    ftpState->fwd->dontRetry(true);

    if (code == 220) {
        if (ftpState->ctrl.message) {
            if (strstr(ftpState->ctrl.message->key, "NetWare"))
                ftpState->flags.skip_whitespace = 1;
        }

        ftpSendUser(ftpState);
    } else if (code == 120) {
        if (NULL != ftpState->ctrl.message)
            debugs(9, DBG_IMPORTANT, "FTP server is busy: " << ftpState->ctrl.message->key);

        return;
    } else {
        ftpFail(ftpState);
    }
}