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
                              ctx->engine_id);
                /* give notice that we're leaving and cancel all ongoing
                 * streams. */
                next_request(ctx, 1); 
                h2_proxy_session_cancel_all(ctx->session);
                h2_proxy_session_process(ctx->session);
                status = ctx->r_status = APR_SUCCESS;
                break;
            }
            if (!ctx->next && h2_proxy_ihash_empty(ctx->session->streams)) {
                break;
            }
        }
        else {
            /* end of processing, maybe error */
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, ctx->owner, 
                          APLOGNO(03375) "eng(%s): end of session %s", 
                          ctx->engine_id, ctx->session->id);
            /*
             * Any open stream of that session needs to
             * a) be reopened on the new session iff safe to do so
             * b) reported as done (failed) otherwise
             */
            h2_proxy_session_cleanup(ctx->session, request_done);
            break;
        }
    }
    
    ctx->session->user_data = NULL;
    ctx->session = NULL;
    
    return status;
}