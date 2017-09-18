ap_log_rerror(APLOG_MARK, APLOG_INFO | APLOG_NOERRNO, 0, r,
                      "proxy: missing or failed auth to %s",
                      apr_uri_unparse(r->pool,
                                 &r->parsed_uri, APR_URI_UNP_OMITPATHINFO));