ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection, 
                          APLOGNO(03371)
                          "h2_proxy_session(%s): failed request %s",
                          ctx->engine_id, task_id);