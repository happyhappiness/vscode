ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
                  "h2_session(%ld): calloc(%ld, %ld)",
                  session->id, (long)n, (long)size);