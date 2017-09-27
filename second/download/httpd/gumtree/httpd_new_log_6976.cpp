ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): idle, no tasks ongoing, %d streams",
                          m->id, (int)h2_ihash_count(m->streams));