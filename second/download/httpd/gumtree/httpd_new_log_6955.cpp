ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, r->connection, 
                          APLOGNO(03369)
                          "h2_proxy_session(%s): rescheduled request %s",
                          ctx->engine_id, task_id);