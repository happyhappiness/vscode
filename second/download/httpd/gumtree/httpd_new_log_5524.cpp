ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03079)
                                  "h2_session(%ld): started on %s:%d", session->id,
                                  session->s->server_hostname,
                                  c->local_addr->port);