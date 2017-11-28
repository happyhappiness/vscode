Http::StatusCode
Ftp::Gateway::failedHttpStatus(err_type &error)
{
    if (error == ERR_NONE) {
        switch (state) {

        case SENT_USER:

        case SENT_PASS:

            if (ctrl.replycode > 500) {
                error = ERR_FTP_FORBIDDEN;
                return password_url ? Http::scForbidden : Http::scUnauthorized;
            } else if (ctrl.replycode == 421) {
                error = ERR_FTP_UNAVAILABLE;
                return Http::scServiceUnavailable;
            }
            break;

        case SENT_CWD:

        case SENT_RETR:
            if (ctrl.replycode == 550) {
                error = ERR_FTP_NOT_FOUND;
                return Http::scNotFound;
            }
            break;

        default:
            break;
        }
    }
    return Ftp::Client::failedHttpStatus(error);
}