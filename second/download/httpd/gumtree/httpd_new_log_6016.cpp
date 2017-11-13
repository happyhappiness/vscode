ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): release_join, waiting on %d worker to report back", 
                          m->id, (int)h2_io_set_size(m->stream_ios));