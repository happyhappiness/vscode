apr_status_t h2_response_trailers_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    h2_task *task = f->ctx;
    h2_from_h1 *from_h1 = task->output? task->output->from_h1 : NULL;
    request_rec *r = f->r;
    apr_bucket *b;
 
    if (from_h1 && from_h1->response) {
        /* Detect the EOR bucket and forward any trailers that may have
         * been set to our h2_response.
         */
        for (b = APR_BRIGADE_FIRST(bb);
             b != APR_BRIGADE_SENTINEL(bb);
             b = APR_BUCKET_NEXT(b))
        {
            if (AP_BUCKET_IS_EOR(b)) {
                /* FIXME: need a better test case than this.
                apr_table_setn(r->trailers_out, "X", "1"); */
                if (r->trailers_out && !apr_is_empty_table(r->trailers_out)) {
                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
                                  "h2_from_h1(%d): trailers filter, saving trailers",
                                  from_h1->stream_id);
                    h2_response_set_trailers(from_h1->response,
                                             apr_table_clone(from_h1->pool, 
                                                             r->trailers_out));
                }
                break;
            }
        }     
    }
     
    return ap_pass_brigade(f->next, bb);
}