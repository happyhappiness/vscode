                set_session_auth(r, sent_user, sent_pw, conf->site);
                if (sent_loc) {
                    apr_table_set(r->headers_out, "Location", sent_loc);
                    return HTTP_MOVED_TEMPORARILY;
                }
                if (conf->loginsuccess) {
                    const char *loginsuccess = ap_expr_str_exec(r,
                            conf->loginsuccess, &err);
                    if (!err) {
                        apr_table_set(r->headers_out, "Location", loginsuccess);
                        return HTTP_MOVED_TEMPORARILY;
                    }
                    else {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02339)
                                      "Can't evaluate login success expression: %s", err);
                        return HTTP_INTERNAL_SERVER_ERROR;
                    }
                }
            }
        }

    }

    /*
     * did the admin prefer to be redirected to the login page on failure
     * instead?
     */
    if (HTTP_UNAUTHORIZED == rv && conf->loginrequired) {
        const char *loginrequired = ap_expr_str_exec(r,
                conf->loginrequired, &err);
        if (!err) {
            apr_table_set(r->headers_out, "Location", loginrequired);
            return HTTP_MOVED_TEMPORARILY;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02340)
                          "Can't evaluate login required expression: %s", err);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    /* did the user ask to be redirected on login success? */
    if (sent_loc) {
        apr_table_set(r->headers_out, "Location", sent_loc);
        rv = HTTP_MOVED_TEMPORARILY;
