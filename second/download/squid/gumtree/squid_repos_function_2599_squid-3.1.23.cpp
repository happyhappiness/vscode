bool
FtpStateData::haveControlChannel(const char *caller_name) const
{
    if (doneWithServer())
        return false;

    /* doneWithServer() only checks BOTH channels are closed. */
    if (ctrl.fd < 0) {
        debugs(9, DBG_IMPORTANT, "WARNING! FTP Server Control channel is closed, but Data channel still active.");
        debugs(9, 2, caller_name << ": attempted on a closed FTP channel.");
        return false;
    }

    return true;
}