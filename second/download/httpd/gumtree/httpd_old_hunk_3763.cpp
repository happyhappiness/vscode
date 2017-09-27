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
            /* hack. Prefix a " if it is a msg; as that is what
             * http_protocol.c relies on to distinguish between
             * a msg and a (local) path.
             */
            conf->response_code_strings[index_number] = (what == MSG) ?
                    apr_pstrcat(cmd->pool, "\"", msg, NULL) :
                    apr_pstrdup(cmd->pool, msg);
        }
    }

    return NULL;
}

