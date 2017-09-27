ap_log_rerror(APLOG_MARK, APLOG_TRACE2, status, stream->r, 
                      "h2_proxy_stream(%s-%d): request body read", 
                      stream->session->id, stream->id);