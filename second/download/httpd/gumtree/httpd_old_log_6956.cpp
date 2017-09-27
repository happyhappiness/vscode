ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%ld-%d): exists, started=%d, scheduled=%d, ready=%d", 
                  m->id, stream->id, stream->started, stream->scheduled,
                  h2_stream_is_ready(stream));