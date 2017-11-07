ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, r->connection, 
                  "h2_proxy_session(%s): request done %s, touched=%d",
                  ctx->engine_id, task_id, touched);