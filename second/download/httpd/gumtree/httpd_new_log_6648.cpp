ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c, 
                      "h2_stream(%ld-%d): input drain returned", 
                      stream->session->id, stream->id);