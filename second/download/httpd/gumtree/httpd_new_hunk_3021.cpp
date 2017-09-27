    r->proxyreq = PROXYREQ_NONE;
    /*
     * Log failed requests if they supplied a password (log username/password
     * guessing attempts)
     */
    if (log_it)
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01035)
                      "missing or failed auth to %s",
                      apr_uri_unparse(r->pool,
                                 &r->parsed_uri, APR_URI_UNP_OMITPATHINFO));

    apr_table_setn(r->err_headers_out, "WWW-Authenticate",
                   apr_pstrcat(r->pool, "Basic realm=\"",
                               apr_uri_unparse(r->pool, &r->parsed_uri,
