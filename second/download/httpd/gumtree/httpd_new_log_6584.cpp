ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                          "h2_session(%ld): keepalive, %f sec left",
                                          session->id, (session->idle_until - now) / 1000000.0f);