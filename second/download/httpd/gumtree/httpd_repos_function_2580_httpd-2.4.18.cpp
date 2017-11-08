static int h2_h2_remove_timeout(conn_rec* c)
{
    h2_ctx *ctx = h2_ctx_get(c);
    
    if (h2_ctx_is_active(ctx) && !h2_ctx_is_task(ctx)) {
        /* cleanup on master h2 connections */
        ap_remove_input_filter_byhandle(c->input_filters, "reqtimeout");
    }
    
    return DECLINED;
}