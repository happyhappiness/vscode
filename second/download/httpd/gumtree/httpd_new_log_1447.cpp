ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "Incoming request is asking for an uncached version of "
                         "%s, but we have been configured to ignore it and serve "
                         "cached content anyway", r->unparsed_uri);