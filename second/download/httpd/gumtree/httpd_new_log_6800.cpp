ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): idle, but %d streams to process",
                          m->id, (int)h2_iq_count(m->q));