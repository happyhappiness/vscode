ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          APLOGNO(03057)
                          "h2_session(%ld): push diary set from Cache-Digest: %s", 
                          session->id, cache_digest);