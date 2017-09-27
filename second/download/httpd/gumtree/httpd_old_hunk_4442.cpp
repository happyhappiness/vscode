    }
    else if (req_engine_pull && ctx->engine) {
        apr_status_t status;
        status = req_engine_pull(ctx->engine, before_leave? 
                                 APR_BLOCK_READ: APR_NONBLOCK_READ, 
                                 ctx->capacity, &ctx->next);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, ctx->owner, 
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
    
    /* Step Four: Send the Request in a new HTTP/2 stream and
     * loop until we got the response or encounter errors.
     */
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, ctx->owner, 
                  "eng(%s): setup session", ctx->engine_id);
    ctx->session = h2_proxy_session_setup(ctx->engine_id, ctx->p_conn, ctx->conf, 
                                          30, h2_log2(ctx->req_buffer_size), 
                                          request_done);
    if (!ctx->session) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->owner, 
                      APLOGNO(03372) "session unavailable");
        return HTTP_SERVICE_UNAVAILABLE;
    }
