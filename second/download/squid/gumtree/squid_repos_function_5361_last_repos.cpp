static void
ftpReadSize(Ftp::Gateway * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code == 213) {
        ftpState->unhack();
        ftpState->theSize = strtoll(ftpState->ctrl.last_reply, NULL, 10);

        if (ftpState->theSize == 0) {
            debugs(9, 2, "SIZE reported " <<
                   ftpState->ctrl.last_reply << " on " <<
                   ftpState->title_url);
            ftpState->theSize = -1;
        }
    } else if (code < 0) {
        ftpFail(ftpState);
        return;
    }

    ftpSendPassive(ftpState);
}