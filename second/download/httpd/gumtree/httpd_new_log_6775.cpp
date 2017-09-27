ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  "h2_proxy_stream(%s-%d): resuming", 
                  session->id, stream->id);