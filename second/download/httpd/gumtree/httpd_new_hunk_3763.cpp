    if (error_number == 401 && what == REMOTE_PATH) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, cmd->server, APLOGNO(00113)
                     "%s:%d cannot use a full URL in a 401 ErrorDocument "
                     "directive --- ignoring!", cmd->directive->filename, cmd->directive->line_num);
    }
    else { /* Store it... */
        if (conf->response_code_exprs == NULL) {
            conf->response_code_exprs = apr_hash_make(cmd->pool);
        }

        if (strcasecmp(msg, "default") == 0) {
            /* special case: ErrorDocument 404 default restores the
             * canned server error response
             */
            apr_hash_set(conf->response_code_exprs,
                    apr_pmemdup(cmd->pool, &index_number, sizeof(index_number)),
                    sizeof(index_number), &errordocument_default);
        }
        else {
            ap_expr_info_t *expr;
            const char *expr_err = NULL;

            /* hack. Prefix a " if it is a msg; as that is what
             * http_protocol.c relies on to distinguish between
             * a msg and a (local) path.
             */
            const char *response =
                    (what == MSG) ? apr_pstrcat(cmd->pool, "\"", msg, NULL) :
                            apr_pstrdup(cmd->pool, msg);

            expr = ap_expr_parse_cmd(cmd, response, AP_EXPR_FLAG_STRING_RESULT,
                    &expr_err, NULL);

            if (expr_err) {
                return apr_pstrcat(cmd->temp_pool,
                                   "Cannot parse expression in ErrorDocument: ",
                                   expr_err, NULL);
            }

            apr_hash_set(conf->response_code_exprs,
                    apr_pmemdup(cmd->pool, &index_number, sizeof(index_number)),
                    sizeof(index_number), expr);

        }
    }

    return NULL;
}

