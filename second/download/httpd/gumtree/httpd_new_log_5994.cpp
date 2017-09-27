ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                              "session(%ld): aborting session, reason=%d %s",
                              session->id, reason, err);