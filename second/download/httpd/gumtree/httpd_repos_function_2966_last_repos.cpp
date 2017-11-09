static int h2_h2_post_read_req(request_rec *r)
{
    /* slave connection? */
    if (r->connection->master) {
        h2_ctx *ctx = h2_ctx_rget(r);
        struct h2_task *task = h2_ctx_get_task(ctx);
        /* This hook will get called twice on internal redirects. Take care
         * that we manipulate filters only once. */
        if (task && !task->filters_set) {
            ap_filter_t *f;
            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, 
                          "h2_task(%s): adding request filters", task->id);

            /* setup the correct filters to process the request for h2 */
            ap_add_input_filter("H2_REQUEST", task, r, r->connection);
            
            /* replace the core http filter that formats response headers
             * in HTTP/1 with our own that collects status and headers */
            ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
            ap_add_output_filter("H2_RESPONSE", task, r, r->connection);
            
            for (f = r->input_filters; f; f = f->next) {
                if (!strcmp("H2_SLAVE_IN", f->frec->name)) {
                    f->r = r;
                    break;
                }
            }
            ap_add_output_filter("H2_TRAILERS_OUT", task, r, r->connection);
            task->filters_set = 1;
        }
    }
    return DECLINED;
}