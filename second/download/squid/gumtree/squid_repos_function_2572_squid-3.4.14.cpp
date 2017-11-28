static void
ftpListDir(FtpStateData * ftpState)
{
    if (ftpState->flags.dir_slash) {
        debugs(9, 3, HERE << "Directory path did not end in /");
        ftpState->title_url.append("/");
        ftpState->flags.isdir = 1;
    }

    ftpSendPassive(ftpState);
}