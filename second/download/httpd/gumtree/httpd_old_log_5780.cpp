ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, m->c, 
                          "h2_mplx(%ld): release_join, %d streams still open", 
                          m->id, (int)h2_io_set_size(m->stream_ios));