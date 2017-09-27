ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01397)
                          "unable to init Zlib: "
                          "inflateInit2 returned %d: URL %s",
                          zRC, r->uri);