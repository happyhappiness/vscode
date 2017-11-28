static void
ftpRestOrList(Ftp::Gateway * ftpState)
{
    debugs(9, 3, HERE);

    if (ftpState->typecode == 'D') {
        ftpState->flags.isdir = 1;

        if (ftpState->flags.put) {
            ftpSendMkdir(ftpState); /* PUT name;type=d */
        } else {
            ftpSendNlst(ftpState);  /* GET name;type=d  sec 3.2.2 of RFC 1738 */
        }
    } else if (ftpState->flags.put) {
        ftpSendStor(ftpState);
    } else if (ftpState->flags.isdir)
        ftpSendList(ftpState);
    else if (ftpState->restartable())
        ftpSendRest(ftpState);
    else
        ftpSendRetr(ftpState);
}