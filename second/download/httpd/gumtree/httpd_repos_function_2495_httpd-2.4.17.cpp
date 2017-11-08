static int h2_h2_post_read_req(request_rec *r)
{
    h2_ctx *ctx = h2_ctx_rget(r);
    struct h2_task_env *env = h2_ctx_get_task(ctx);
    if (env) {
        /* h2_task connection for a stream, not for h2c */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "adding h1_to_h2_resp output filter");
        if (env->serialize_headers) {
            ap_remove_output_filter_byhandle(r->output_filters, "H1_TO_H2_RESP");
            ap_add_output_filter("H1_TO_H2_RESP", env, r, r->connection);
        }
        else {
            /* replace the core http filter that formats response headers
             * in HTTP/1 with our own that collects status and headers */
            ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
            ap_remove_output_filter_byhandle(r->output_filters, "H2_RESPONSE");
            ap_add_output_filter("H2_RESPONSE", env, r, r->connection);
        }
    }
    return DECLINED;
}