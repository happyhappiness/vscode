    v.r = r;
    v.encoded = NULL;
    v.new_cookies = apr_table_make(r->pool, 10);
    v.duplicated = 0;
    v.name = name;

    apr_table_do((int (*) (void *, const char *, const char *))
                 extract_cookie_line, (void *) &v, r->headers_in,
                 "Cookie", "Cookie2", NULL);
    if (v.duplicated) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00011) LOG_PREFIX
         "client submitted cookie '%s' more than once: %s", v.name, r->uri);
        return APR_EGENERAL;
    }
