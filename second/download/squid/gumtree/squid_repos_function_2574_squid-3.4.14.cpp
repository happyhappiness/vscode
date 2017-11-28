static void
ftpReadMdtm(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code == 213) {
        ftpState->mdtm = parse_iso3307_time(ftpState->ctrl.last_reply);
        ftpState->unhack();
    } else if (code < 0) {
        ftpFail(ftpState);
        return;
    }

    ftpSendSize(ftpState);
}