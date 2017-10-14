ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%ld): destroy, tasks=%d", 
                  m->id, (int)h2_ihash_count(m->tasks));