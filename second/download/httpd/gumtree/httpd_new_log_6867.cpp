ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
                      APLOG_ERR : APLOG_DEBUG, 0, session->c,  
                      H2_STRM_LOG(APLOGNO(02936), stream, "resumed"));