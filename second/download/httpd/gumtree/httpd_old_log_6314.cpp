ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, r->connection, 
                          APLOGNO(03471) "h2_proxy_session(%s): request %s -> %s "
                          "not complete, was touched",
                          ctx->engine_id, task_id, uri);