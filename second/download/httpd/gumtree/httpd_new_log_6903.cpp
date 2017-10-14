ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c,
                  H2_STRM_MSG(stream, "dispatch event %d"), ev);