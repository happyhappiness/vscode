ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "proxy: no HTTP 0.9 request (with no host line) "
                          "on incoming request and preserve host set "
                          "forcing hostname to be %s for uri %s",
                          hostname,
                          r->uri );