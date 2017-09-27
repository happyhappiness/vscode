     */
    apr_table_addn(r->headers_out, "Cache-Control", "no-store");
    apr_table_addn(r->err_headers_out, "Cache-Control", "no-store");

    /* if set, internal redirect to the logout page */
    if (conf->logout) {
        const char *logout = ap_expr_str_exec(r,
                conf->logout, &err);
        if (!err) {
            apr_table_addn(r->headers_out, "Location", logout);
            return HTTP_TEMPORARY_REDIRECT;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02343)
                          "Can't evaluate logout expression: %s", err);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    return HTTP_OK;

}

