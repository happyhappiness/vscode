ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, c,
                                  "h2_session(%ld): waiting on conditional",
                                  session->id);