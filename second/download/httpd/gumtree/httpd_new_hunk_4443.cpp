        
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
