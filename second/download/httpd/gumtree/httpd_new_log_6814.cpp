ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          H2_STRM_LOG(APLOGNO(03065), stream, 
                          "closing with err=%d %s"), 
                          (int)error_code, h2_h2_err_description(error_code));