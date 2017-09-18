    else
        what = MSG;

    /* The entry should be ignored if it is a full URL for a 401 error */

    if (error_number == 401 && what == REMOTE_PATH) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, cmd->server,
                     "cannot use a full URL in a 401 ErrorDocument "
                     "directive --- ignoring!");
    }
    else { /* Store it... */
        if (conf->response_code_strings == NULL) {
            conf->response_code_strings =
