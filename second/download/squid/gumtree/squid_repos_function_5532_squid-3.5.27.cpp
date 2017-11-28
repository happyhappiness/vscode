static void
ftpFail(Ftp::Gateway *ftpState)
{
    int code = ftpState->ctrl.replycode;
    err_type error_code = ERR_NONE;

    debugs(9, 6, "state " << ftpState->state <<
           " reply code " << code << "flags(" <<
           (ftpState->flags.isdir?"IS_DIR,":"") <<
           (ftpState->flags.try_slash_hack?"TRY_SLASH_HACK":"") << "), " <<
           "mdtm=" << ftpState->mdtm << ", size=" << ftpState->theSize <<
           "slashhack=" << (ftpState->request->urlpath.caseCmp("/%2f", 4)==0? "T":"F") );

    /* Try the / hack to support "Netscape" FTP URL's for retreiving files */
    if (!ftpState->flags.isdir &&   /* Not a directory */
            !ftpState->flags.try_slash_hack &&  /* Not in slash hack */
            ftpState->mdtm <= 0 && ftpState->theSize < 0 && /* Not known as a file */
            ftpState->request->urlpath.caseCmp("/%2f", 4) != 0) {   /* No slash encoded */

        switch (ftpState->state) {

        case Ftp::Client::SENT_CWD:

        case Ftp::Client::SENT_RETR:
            /* Try the / hack */
            ftpState->hackShortcut(ftpTrySlashHack);
            return;

        default:
            break;
        }
    }

    Http::StatusCode sc = ftpState->failedHttpStatus(error_code);
    ErrorState *ftperr = new ErrorState(error_code, sc, ftpState->fwd->request);
    ftpState->failed(error_code, code, ftperr);
    ftperr->detailError(code);
    HttpReply *newrep = ftperr->BuildHttpReply();
    delete ftperr;

    ftpState->entry->replaceHttpReply(newrep);
    ftpSendQuit(ftpState);
}