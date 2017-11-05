static void request_done(h2_proxy_ctx *ctx, request_rec *r,
                         apr_status_t status, int touched)
{   
    const char *task_id = apr_table_get(r->connection->notes, H2_TASK_ID_NOTE);

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, r->connection, 
                  "h2_proxy_session(%s): request done %s, touched=%d",
                  ctx->engine_id, task_id, touched);
    if (status != APR_SUCCESS) {
        if (!touched) {
            /* untouched request, need rescheduling */
            status = h2_proxy_fifo_push(ctx->requests, r);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, r->connection, 
                          APLOGNO(03369)
                          "h2_proxy_session(%s): rescheduled request %s",
                          ctx->engine_id, task_id);
            return;
        }
        else {
            const char *uri;
            uri = apr_uri_unparse(r->pool, &r->parsed_uri, 0);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, r->connection, 
                          APLOGNO(03471) "h2_proxy_session(%s): request %s -> %s "
                          "not complete, cannot repeat", 
                          ctx->engine_id, task_id, uri);
        }
    }
    
    if (r == ctx->rbase) {
        ctx->r_status = ((status == APR_SUCCESS)? APR_SUCCESS
                         : HTTP_SERVICE_UNAVAILABLE);
    }
    
    if (req_engine_done && ctx->engine) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, r->connection, 
                      APLOGNO(03370)
                      "h2_proxy_session(%s): finished request %s",
                      ctx->engine_id, task_id);
        req_engine_done(ctx->engine, r->connection, status);
    }
}