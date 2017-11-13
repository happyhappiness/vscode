ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c, 
                  H2_STRM_MSG(stream, "transit to [%s]"), h2_ss_str(new_state));