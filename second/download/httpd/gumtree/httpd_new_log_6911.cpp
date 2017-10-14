ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c, 
                          H2_STRM_MSG(stream, "input drain returned"));