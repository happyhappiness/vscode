ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
                  "h2_session(%ld): realloc(%ld)",
                  session->id, (long)size);