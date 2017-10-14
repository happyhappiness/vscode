ap_log_cerror(APLOG_MARK, loglvl, 0, session->c, APLOGNO(03078)
                      "h2_session(%ld): transit [%s] -- %s --> [%s]", session->id,
                      state_name(session->state), action, state_name(nstate));