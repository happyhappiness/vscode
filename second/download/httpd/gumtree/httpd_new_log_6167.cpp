ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  H2_STRM_MSG(stream, "started=%d, scheduled=%d, ready=%d, "
                              "out_buffer=%ld"), 
                  !!stream->task, stream->scheduled, h2_stream_is_ready(stream),
                  (long)h2_beam_get_buffered(stream->output));