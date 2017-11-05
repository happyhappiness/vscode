ap_log_cerror(APLOG_MARK, (attempts? APLOG_INFO : APLOG_DEBUG), 
                          0, m->c,
                          "h2_mplx(%ld): release_join, refs=%d, waiting...", 
                          m->id, m->refs);