ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      H2_SSSN_LOG(APLOGNO(03069), session, 
                                  "sent GOAWAY, err=%d, msg=%s"), error, msg? msg : "");