ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
                          "h2_mplx(%ld-%d): close with eor=%s", 
                          m->id, io->id, io->eor? "yes" : "no");