ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                                  H2_STRM_MSG(stream, "output closed=%d, mplx idle"
                                              ", out has %ld bytes buffered"),
                                  h2_beam_is_closed(stream->output),
                                  (long)h2_beam_get_buffered(stream->output));