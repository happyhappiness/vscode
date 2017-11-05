ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
                      "h2_mplx(%ld): release_join -> destroy, (#ios=%ld)", 
                      m->id, (long)h2_io_set_size(m->stream_ios));