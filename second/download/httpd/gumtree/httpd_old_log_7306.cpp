ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01092)
                          "no HTTP 0.9 request (with no host line) "
                          "on incoming request and preserve host set "
                          "forcing hostname to be %s for uri %s",
                          hostname, r->uri);