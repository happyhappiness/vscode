ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c, 
                              "h2_proxy_stream(%s-%d): resuming", 
                              session->id, stream_id);