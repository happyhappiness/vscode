ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, 
                      H2_STRM_LOG(APLOGNO(03072), stream, "submit %d trailers"), 
                      (int)nh->nvlen);