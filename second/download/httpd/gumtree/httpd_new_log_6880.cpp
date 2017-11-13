ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, 
                                  H2_SSSN_LOG(APLOGNO(03079), session, 
                                  "started on %s:%d"), 
                                  session->s->server_hostname,
                                  c->local_addr->port);