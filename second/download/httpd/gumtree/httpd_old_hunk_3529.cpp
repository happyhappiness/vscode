    apr_table_do(set_cookie_doo_doo, cookie_table, r->err_headers_out, "Set-Cookie", NULL);

    while (1) {

        int rv = (*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data);
        if (rv == 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                          "Premature end of script headers: %s",
                          apr_filepath_name_get(r->filename));
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        else if (rv == -1) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                          "Script timed out before returning headers: %s",
                          apr_filepath_name_get(r->filename));
            return HTTP_GATEWAY_TIME_OUT;
        }

        /* Delete terminal (CR?)LF */
