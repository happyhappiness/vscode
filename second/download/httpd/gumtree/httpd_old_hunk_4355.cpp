         * is still ongoing. */
        return h2_conn_pre_close(ctx, c);
    }
    return DECLINED;
}

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
            
            /* setup the correct output filters to process the response
             * on the proper mod_http2 way. */
            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "adding task output filter");
            if (task->ser_headers) {
                ap_add_output_filter("H1_TO_H2_RESP", task, r, r->connection);
            }
            else {
                /* replace the core http filter that formats response headers
                 * in HTTP/1 with our own that collects status and headers */
                ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
                ap_add_output_filter("H2_RESPONSE", task, r, r->connection);
            }
            
            /* trailers processing. Incoming trailers are added to this
             * request via our h2 input filter, outgoing trailers
             * in a special h2 out filter. */
            for (f = r->input_filters; f; f = f->next) {
                if (!strcmp("H2_TO_H1", f->frec->name)) {
                    f->r = r;
                    break;
                }
            }
            ap_add_output_filter("H2_TRAILERS", task, r, r->connection);
            task->filters_set = 1;
        }
    }
    return DECLINED;
}

