ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%ld-%d): exists, started=%d, scheduled=%d, "
                  "submitted=%d, suspended=%d", 
                  m->id, stream->id, stream->started, stream->scheduled,
                  stream->submitted, stream->suspended);