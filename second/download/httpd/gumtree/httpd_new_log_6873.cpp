ap_log_cerror(APLOG_MARK, loglvl, 0, session->c, 
                      H2_SSSN_LOG(APLOGNO(03078), session, 
                      "transit [%s] -- %s --> [%s]"), 
                      h2_session_state_str(session->state), action, 
                      h2_session_state_str(nstate));