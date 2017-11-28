void
FtpStateData::failedErrorMessage(err_type error, int xerrno)
{
    ErrorState *ftperr = NULL;
    const char *command, *reply;

    /* Translate FTP errors into HTTP errors */
    switch (error) {

    case ERR_NONE:

        switch (state) {

        case SENT_USER:

        case SENT_PASS:

            if (ctrl.replycode > 500)
                if (password_url)
                    ftperr = new ErrorState(ERR_FTP_FORBIDDEN, Http::scForbidden, fwd->request);
                else
                    ftperr = new ErrorState(ERR_FTP_FORBIDDEN, Http::scUnauthorized, fwd->request);

            else if (ctrl.replycode == 421)
                ftperr = new ErrorState(ERR_FTP_UNAVAILABLE, Http::scServiceUnavailable, fwd->request);

            break;

        case SENT_CWD:

        case SENT_RETR:
            if (ctrl.replycode == 550)
                ftperr = new ErrorState(ERR_FTP_NOT_FOUND, Http::scNotFound, fwd->request);

            break;

        default:
            break;
        }

        break;

    case ERR_READ_TIMEOUT:
        ftperr = new ErrorState(error, Http::scGatewayTimeout, fwd->request);
        break;

    default:
        ftperr = new ErrorState(error, Http::scBadGateway, fwd->request);
        break;
    }

    if (ftperr == NULL)
        ftperr = new ErrorState(ERR_FTP_FAILURE, Http::scBadGateway, fwd->request);

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

    entry->replaceHttpReply( ftperr->BuildHttpReply() );
    delete ftperr;
}