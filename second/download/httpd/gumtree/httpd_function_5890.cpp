static int h2_task_process_conn(conn_rec* c)
{
    h2_ctx *ctx = h2_ctx_get(c);
    
    if (h2_ctx_is_task(ctx)) {
        if (!ctx->task_env->serialize_headers) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, 
                          "h2_h2, processing request directly");
            h2_task_process_request(ctx->task_env);
            return DONE;
        }
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, 
                      "h2_task(%s), serialized handling", ctx->task_env->id);
    }
    return DECLINED;
}