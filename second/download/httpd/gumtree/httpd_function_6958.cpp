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