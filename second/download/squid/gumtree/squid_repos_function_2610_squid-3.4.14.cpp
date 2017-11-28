static void
ftpFail(FtpStateData *ftpState)
{
    debugs(9, 6, HERE << "flags(" <<
           (ftpState->flags.isdir?"IS_DIR,":"") <<
           (ftpState->flags.try_slash_hack?"TRY_SLASH_HACK":"") << "), " <<
           "mdtm=" << ftpState->mdtm << ", size=" << ftpState->theSize <<
           "slashhack=" << (ftpState->request->urlpath.caseCmp("/%2f", 4)==0? "T":"F") );

    /* Try the / hack to support "Netscape" FTP URL's for retreiving files */
    if (!ftpState->flags.isdir &&	/* Not a directory */
            !ftpState->flags.try_slash_hack &&	/* Not in slash hack */
            ftpState->mdtm <= 0 && ftpState->theSize < 0 &&	/* Not known as a file */
            ftpState->request->urlpath.caseCmp("/%2f", 4) != 0) {	/* No slash encoded */

        switch (ftpState->state) {

        case SENT_CWD:

        case SENT_RETR:
            /* Try the / hack */
            ftpState->hackShortcut(ftpTrySlashHack);
            return;

        default:
            break;
        }
    }

    ftpState->failed(ERR_NONE, 0);
    /* failed() closes ctrl.conn and frees this */
}