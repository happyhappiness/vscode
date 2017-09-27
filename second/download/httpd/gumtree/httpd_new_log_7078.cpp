ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, stream->session->c, 
                      H2_STRM_LOG(APLOGNO(10002), stream, "invalid event %d"), ev);