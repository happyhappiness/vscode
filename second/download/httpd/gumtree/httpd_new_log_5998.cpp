ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03364)
                      "h2_proxy_sesssion(%s): stream(%d) closed "
                      "(touched=%d, error=%d)", 
                      session->id, stream_id, touched, stream->error_code);