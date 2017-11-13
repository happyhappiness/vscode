ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,
                              APLOGNO(02952) 
                              "h2_mplx(%ld): join attempts exhausted, refs=%d", 
                              m->id, m->refs);