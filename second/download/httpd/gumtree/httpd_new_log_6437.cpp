ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                      "h2_session(%ld): [%s] process returns", 
                      session->id, state_name(session->state));