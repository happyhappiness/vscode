ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
                      "select protocol from %s, choices=%s for server %s", 
                      p, apr_array_pstrcat(pool, choices, ','),
                      s->server_hostname);