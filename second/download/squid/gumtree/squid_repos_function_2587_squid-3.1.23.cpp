void
FtpStateData::failedErrorMessage(err_type error, int xerrno)
{
    ErrorState *ftperr;
    const char *command, *reply;

    /* Translate FTP errors into HTTP errors */
    ftperr = NULL;

    switch (error) {

    case ERR_NONE:

        switch (state) {

        case SENT_USER:

        case SENT_PASS:

            if (ctrl.replycode > 500)
                if (password_url)
                    ftperr = errorCon(ERR_FTP_FORBIDDEN, HTTP_FORBIDDEN, fwd->request);
                else
                    ftperr = errorCon(ERR_FTP_FORBIDDEN, HTTP_UNAUTHORIZED, fwd->request);

            else if (ctrl.replycode == 421)
                ftperr = errorCon(ERR_FTP_UNAVAILABLE, HTTP_SERVICE_UNAVAILABLE, fwd->request);

            break;

        case SENT_CWD:

        case SENT_RETR:
            if (ctrl.replycode == 550)
                ftperr = errorCon(ERR_FTP_NOT_FOUND, HTTP_NOT_FOUND, fwd->request);

            break;

        default:
            break;
        }

        break;

    case ERR_READ_TIMEOUT:
        ftperr = errorCon(error, HTTP_GATEWAY_TIMEOUT, fwd->request);
        break;

    default:
        ftperr = errorCon(error, HTTP_BAD_GATEWAY, fwd->request);
        break;
    }

    if (ftperr == NULL)
        ftperr = errorCon(ERR_FTP_FAILURE, HTTP_BAD_GATEWAY, fwd->request);

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
    errorStateFree(ftperr);
}