ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
                              APLOGNO(03080)
                              "h2_session(%ld): unknown state %d", session->id, session->state);