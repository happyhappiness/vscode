static apr_status_t next_request(h2_proxy_ctx *ctx, int before_leave)
{
    if (h2_proxy_fifo_count(ctx->requests) > 0) {
        return APR_SUCCESS;
    }
    else if (req_engine_pull && ctx->engine) {
        apr_status_t status;
        request_rec *r = NULL;
        
        status = req_engine_pull(ctx->engine, before_leave? 
                                 APR_BLOCK_READ: APR_NONBLOCK_READ, 
                                 ctx->capacity, &r);
        if (status == APR_SUCCESS && r) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, ctx->owner, 
                          "h2_proxy_engine(%s): pulled request (%s) %s", 
                          ctx->engine_id, 
                          before_leave? "before leave" : "regular", 
                          r->the_request);
            h2_proxy_fifo_push(ctx->requests, r);
        }
        return APR_STATUS_IS_EAGAIN(status)? APR_SUCCESS : status;
    }
    return APR_EOF;
}