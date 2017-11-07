ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): 2. release_join with %d streams to purge", 
                          m->id, (int)h2_ihash_count(m->spurge));