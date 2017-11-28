void
FtpStateData::loginFailed()
{
    ErrorState *err = NULL;
    const char *command, *reply;

    if ((state == SENT_USER || state == SENT_PASS) && ctrl.replycode >= 400) {
        if (ctrl.replycode == 421 || ctrl.replycode == 426) {
            // 421/426 - Service Overload - retry permitted.
            err = errorCon(ERR_FTP_UNAVAILABLE, HTTP_SERVICE_UNAVAILABLE, fwd->request);
        } else if (ctrl.replycode >= 430 && ctrl.replycode <= 439) {
            // 43x - Invalid or Credential Error - retry challenge required.
            err = errorCon(ERR_FTP_FORBIDDEN, HTTP_UNAUTHORIZED, fwd->request);
        } else if (ctrl.replycode >= 530 && ctrl.replycode <= 539) {
            // 53x - Credentials Missing - retry challenge required
            if (password_url) // but they were in the URI! major fail.
                err = errorCon(ERR_FTP_FORBIDDEN, HTTP_FORBIDDEN, fwd->request);
            else
                err = errorCon(ERR_FTP_FORBIDDEN, HTTP_UNAUTHORIZED, fwd->request);
        }
    }

    // any other problems are general falures.
    if (!err) {
        ftpFail(this);
        return;
    }

    err->ftp.server_msg = ctrl.message;

    ctrl.message = NULL;

    if (old_request)
        command = old_request;
    else
        command = ctrl.last_command;

    if (command && strncmp(command, "PASS", 4) == 0)
        command = "PASS <yourpassword>";

    if (old_reply)
        reply = old_reply;
    else
        reply = ctrl.last_reply;

    if (command)
        err->ftp.request = xstrdup(command);

    if (reply)
        err->ftp.reply = xstrdup(reply);


    HttpReply *newrep = err->BuildHttpReply();
    errorStateFree(err);
    /* add Authenticate header */
    newrep->header.putAuth("Basic", ftpRealm());

    // add it to the store entry for response....
    entry->replaceHttpReply(newrep);
    serverComplete();
}