static void
ftpFail(Ftp::Gateway *ftpState)
{
    const bool slashHack = ftpState->request->url.path().caseCmp("/%2f", 4)==0;
    int code = ftpState->ctrl.replycode;
    err_type error_code = ERR_NONE;

    debugs(9, 6, "state " << ftpState->state <<
           " reply code " << code << "flags(" <<
           (ftpState->flags.isdir?"IS_DIR,":"") <<
           (ftpState->flags.try_slash_hack?"TRY_SLASH_HACK":"") << "), " <<
           "mdtm=" << ftpState->mdtm << ", size=" << ftpState->theSize <<
           "slashhack=" << (slashHack? "T":"F"));

    /* Try the / hack to support "Netscape" FTP URL's for retreiving files */
    if (!ftpState->flags.isdir &&   /* Not a directory */
            !ftpState->flags.try_slash_hack && !slashHack && /* Not doing slash hack */
            ftpState->mdtm <= 0 && ftpState->theSize < 0) { /* Not known as a file */

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