ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03065)
                      "h2_stream(%ld-%d): closing with err=%d %s", 
                      session->id, (int)stream->id, (int)error_code,
                      h2_h2_err_description(error_code));