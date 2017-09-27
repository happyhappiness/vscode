ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01383)
                              "unable to init Zlib: "
                              "deflateInit2 returned %d: URL %s",
                              zRC, r->uri);