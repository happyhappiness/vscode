                                         domain, NULL);
    nuri = apr_uri_unparse(r->pool,
                           &r->parsed_uri,
                           APR_URI_UNP_REVEALPASSWORD);

    apr_table_set(r->headers_out, "Location", nuri);
    ap_log_rerror(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r,
                  "Domain missing: %s sent to %s%s%s", r->uri,
                  apr_uri_unparse(r->pool, &r->parsed_uri,
                                  APR_URI_UNP_OMITUSERINFO),
                  ref ? " from " : "", ref ? ref : "");

    return HTTP_MOVED_PERMANENTLY;
