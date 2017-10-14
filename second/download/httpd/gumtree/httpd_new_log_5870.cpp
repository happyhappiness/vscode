ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
                      "h2_stream(%ld-%d): output closed", 
                      stream->session->id, stream->id);