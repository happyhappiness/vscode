        what = MSG;

    /* The entry should be ignored if it is a full URL for a 401 error */

    if (error_number == 401 && what == REMOTE_PATH) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, cmd->server, APLOGNO(00113)
                     "%s:%d cannot use a full URL in a 401 ErrorDocument "
                     "directive --- ignoring!", cmd->directive->filename, cmd->directive->line_num);
    }
    else { /* Store it... */
        if (conf->response_code_strings == NULL) {
            conf->response_code_strings =
                apr_pcalloc(cmd->pool,
                            sizeof(*conf->response_code_strings) *
                            RESPONSE_CODES);
        }

        if (strcasecmp(msg, "default") == 0) {
            /* special case: ErrorDocument 404 default restores the
             * canned server error response
             */
            conf->response_code_strings[index_number] = &errordocument_default;
        }
        else {
