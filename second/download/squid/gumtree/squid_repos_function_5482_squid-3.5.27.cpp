void
Ftp::Gateway::loginFailed()
{
    ErrorState *err = NULL;

    if ((state == SENT_USER || state == SENT_PASS) && ctrl.replycode >= 400) {
        if (ctrl.replycode == 421 || ctrl.replycode == 426) {
            // 421/426 - Service Overload - retry permitted.
            err = new ErrorState(ERR_FTP_UNAVAILABLE, Http::scServiceUnavailable, fwd->request);
        } else if (ctrl.replycode >= 430 && ctrl.replycode <= 439) {
            // 43x - Invalid or Credential Error - retry challenge required.
            err = new ErrorState(ERR_FTP_FORBIDDEN, Http::scUnauthorized, fwd->request);
        } else if (ctrl.replycode >= 530 && ctrl.replycode <= 539) {
            // 53x - Credentials Missing - retry challenge required
            if (password_url) // but they were in the URI! major fail.
                err = new ErrorState(ERR_FTP_FORBIDDEN, Http::scForbidden, fwd->request);
            else
                err = new ErrorState(ERR_FTP_FORBIDDEN, Http::scUnauthorized, fwd->request);
        }
    }

    if (!err) {
        ftpFail(this);
        return;
    }

    failed(ERR_NONE, ctrl.replycode, err);
    // any other problems are general falures.

    HttpReply *newrep = err->BuildHttpReply();
    delete err;

#if HAVE_AUTH_MODULE_BASIC
    /* add Authenticate header */
    // XXX: performance regression. c_str() may reallocate
    SBuf realm(ftpRealm()); // local copy so SBuf wont disappear too early
    newrep->header.putAuth("Basic", realm.c_str());
#endif

    // add it to the store entry for response....
    entry->replaceHttpReply(newrep);
    serverComplete();
}