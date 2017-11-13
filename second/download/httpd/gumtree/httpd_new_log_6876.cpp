ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          H2_SSSN_MSG(session, "unknown event %d"), ev);