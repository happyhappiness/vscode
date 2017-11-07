ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): release_join with %d streams open, "
                          "%d streams resume, %d streams ready, %d tasks", 
                          m->id, (int)h2_ihash_count(m->streams),
                          (int)h2_ihash_count(m->sresume), 
                          (int)h2_ihash_count(m->sready), 
                          (int)h2_ihash_count(m->tasks));