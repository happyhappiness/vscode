ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session(%ld): starting on %s:%d", session->id,
                  session->c->base_server->defn_name,
                  session->c->local_addr->port);