     */
    auth_line = apr_pstrcat(r->pool, "Basic ",
                            ap_pbase64encode(r->pool,
                                             apr_pstrcat(r->pool, clientdn,
                                                         ":password", NULL)),
                            NULL);
    apr_table_set(r->headers_in, "Authorization", auth_line);

    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                  "Faking HTTP Basic Auth header: \"Authorization: %s\"",
                  auth_line);

    return DECLINED;
}

