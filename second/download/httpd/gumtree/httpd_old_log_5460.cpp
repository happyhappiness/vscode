ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, m->c,
                              "h2_mplx(%ld-%d): close with trailers=%s", 
                              m->id, io->id, trailers? "yes" : "no");