void
Ftp::Client::failed(err_type error, int xerrno, ErrorState *err)
{
    debugs(9, 3, "entry-null=" << (entry?entry->isEmpty():0) << ", entry=" << entry);

    const char *command, *reply;
    ErrorState *ftperr;

    if (err) {
        debugs(9, 6, "error=" << err->type << ", code=" << xerrno <<
               ", status=" << err->httpStatus);
        error = err->type;
        ftperr = err;
    } else {
        Http::StatusCode httpStatus = failedHttpStatus(error);
        ftperr = new ErrorState(error, httpStatus, fwd->request);
    }

    ftperr->xerrno = xerrno;

    ftperr->ftp.server_msg = ctrl.message;
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
        ftperr->ftp.request = xstrdup(command);

    if (reply)
        ftperr->ftp.reply = xstrdup(reply);

    if (!err) {
        fwd->request->detailError(error, xerrno);
        fwd->fail(ftperr);
        closeServer(); // we failed, so no serverComplete()
    }
}