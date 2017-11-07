static int h2_h2_post_read_req(request_rec *r)
{
    h2_ctx *ctx = h2_ctx_rget(r);
    struct h2_task *task = h2_ctx_get_task(ctx);
    if (task) {
        /* FIXME: sometimes, this hook gets called twice for a single request.
         * This should not be, right? */
        /* h2_task connection for a stream, not for h2c */
        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                      "adding h1_to_h2_resp output filter");
        if (task->serialize_headers) {
            ap_remove_output_filter_byhandle(r->output_filters, "H1_TO_H2_RESP");
            ap_add_output_filter("H1_TO_H2_RESP", task, r, r->connection);
        }
        else {
            /* replace the core http filter that formats response headers
             * in HTTP/1 with our own that collects status and headers */
            ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
            ap_remove_output_filter_byhandle(r->output_filters, "H2_RESPONSE");
            ap_add_output_filter("H2_RESPONSE", task, r, r->connection);
        }
        ap_add_output_filter("H2_TRAILERS", task, r, r->connection);
    }
    return DECLINED;
}