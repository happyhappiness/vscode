{
    h2_task *task = f->ctx;
    request_rec *r = f->r;
    apr_bucket *b, *bresp, *body_bucket = NULL, *next;
    ap_bucket_error *eb = NULL;
    h2_headers *response = NULL;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_task(%s): output_filter called", task->id);
    
    if (!task->output.sent_response) {
        /* check, if we need to send the response now. Until we actually
         * see a DATA bucket or some EOS/EOR, we do not do so. */
        for (b = APR_BRIGADE_FIRST(bb);
             b != APR_BRIGADE_SENTINEL(bb);
             b = APR_BUCKET_NEXT(b))
        {
