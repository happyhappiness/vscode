                      ctx->p_conn->hostname: "", session->c->client_ip, 
                      session->c->remote_host ? session->c->remote_host: "");
    }
    return status;
}

static void request_done(h2_proxy_session *session, request_rec *r,
                         apr_status_t status, int touched)
{   
    h2_proxy_ctx *ctx = session->user_data;
    const char *task_id = apr_table_get(r->connection->notes, H2_TASK_ID_NOTE);

    if (status != APR_SUCCESS) {
        if (!touched) {
            /* untouched request, need rescheduling */
            if (req_engine_push && is_h2 && is_h2(ctx->owner)) {
                if (req_engine_push(ctx->engine_type, r, NULL) == APR_SUCCESS) {
                    /* push to engine */
                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection, 
                                  APLOGNO(03369)
                                  "h2_proxy_session(%s): rescheduled request %s",
                                  ctx->engine_id, task_id);
                    return;
                }
            }
        }
        else {
            const char *uri;
            uri = apr_uri_unparse(r->pool, &r->parsed_uri, 0);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, r->connection, 
                          APLOGNO(03471) "h2_proxy_session(%s): request %s -> %s "
                          "not complete, was touched",
                          ctx->engine_id, task_id, uri);
        }
    }
    
    if (r == ctx->rbase) {
        ctx->r_status = (status == APR_SUCCESS)? APR_SUCCESS : HTTP_SERVICE_UNAVAILABLE;
    }
    
    if (req_engine_done && ctx->engine) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, r->connection, 
                      APLOGNO(03370)
                      "h2_proxy_session(%s): finished request %s",
                      ctx->engine_id, task_id);
        req_engine_done(ctx->engine, r->connection, status);
    }
}    

static apr_status_t next_request(h2_proxy_ctx *ctx, int before_leave)
{
    if (ctx->next) {
        return APR_SUCCESS;
    }
    else if (req_engine_pull && ctx->engine) {
        apr_status_t status;
        status = req_engine_pull(ctx->engine, before_leave? 
                                 APR_BLOCK_READ: APR_NONBLOCK_READ, 
                                 ctx->capacity, &ctx->next);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, ctx->owner, 
                      "h2_proxy_engine(%s): pulled request (%s) %s", 
                      ctx->engine_id, 
                      before_leave? "before leave" : "regular", 
                      (ctx->next? ctx->next->the_request : "NULL"));
        return APR_STATUS_IS_EAGAIN(status)? APR_SUCCESS : status;
    }
    return APR_EOF;
}

static apr_status_t proxy_engine_run(h2_proxy_ctx *ctx) {
    apr_status_t status = OK;
    int h2_front;
    
    /* Step Four: Send the Request in a new HTTP/2 stream and
     * loop until we got the response or encounter errors.
     */
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, ctx->owner, 
                  "eng(%s): setup session", ctx->engine_id);
    h2_front = is_h2? is_h2(ctx->owner) : 0;
    ctx->session = h2_proxy_session_setup(ctx->engine_id, ctx->p_conn, ctx->conf,
                                          h2_front, 30, 
                                          h2_proxy_log2((int)ctx->req_buffer_size), 
                                          request_done);
    if (!ctx->session) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->owner, 
                      APLOGNO(03372) "session unavailable");
        return HTTP_SERVICE_UNAVAILABLE;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->owner, APLOGNO(03373)
                  "eng(%s): run session %s", ctx->engine_id, ctx->session->id);
    ctx->session->user_data = ctx;
    
    while (1) {
        if (ctx->next) {
            add_request(ctx->session, ctx->next);
            ctx->next = NULL;
        }
        
        status = h2_proxy_session_process(ctx->session);
        
        if (status == APR_SUCCESS) {
            apr_status_t s2;
            /* ongoing processing, call again */
            if (ctx->session->remote_max_concurrent > 0
                && ctx->session->remote_max_concurrent != ctx->capacity) {
                ctx->capacity = (int)ctx->session->remote_max_concurrent;
            }
            s2 = next_request(ctx, 0);
            if (s2 == APR_ECONNABORTED) {
                /* master connection gone */
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, s2, ctx->owner, 
                              APLOGNO(03374) "eng(%s): pull request", 
