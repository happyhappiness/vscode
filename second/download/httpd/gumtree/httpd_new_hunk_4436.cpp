    if (!c->master) {
        return DECLINED;
    }
    
    ctx = h2_ctx_get(c, 0);
    if (h2_ctx_is_task(ctx)) {
        if (!ctx->task->request->serialize) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                          "h2_h2, processing request directly");
            h2_task_process_request(ctx->task, c);
            return DONE;
        }
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
