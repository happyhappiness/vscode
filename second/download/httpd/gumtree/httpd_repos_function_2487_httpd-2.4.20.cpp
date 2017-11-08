int h2_filter_h2_status_handler(request_rec *r)
{
    h2_ctx *ctx = h2_ctx_rget(r);
    h2_task *task;
    
    if (strcmp(r->handler, "http2-status")) {
        return DECLINED;
    }
    if (r->method_number != M_GET) {
        return DECLINED;
    }

    task = ctx? h2_ctx_get_task(ctx) : NULL;
    if (task) {
        /* We need to handle the actual output on the main thread, as
         * we need to access h2_session information. */
        apr_table_setn(r->notes, H2_RESP_SOS_NOTE, H2_SOS_H2_STATUS);
        apr_table_setn(r->headers_out, "Content-Type", "application/json");
        r->status = 200;
        return DONE;
    }
    return DECLINED;
}