ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03366)
                      "h2_proxy_session(%s): cancel  %d streams",
                      session->id, (int)h2_proxy_ihash_count(session->streams));