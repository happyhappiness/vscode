apr_status_t h2_filter_trailers_out(ap_filter_t *f, apr_bucket_brigade *bb)
{
    h2_task *task = f->ctx;
    request_rec *r = f->r;
    apr_bucket *b, *e;
 
    if (task && r) {
        /* Detect the EOS/EOR bucket and forward any trailers that may have
         * been set to our h2_headers.
         */
        for (b = APR_BRIGADE_FIRST(bb);
             b != APR_BRIGADE_SENTINEL(bb);
             b = APR_BUCKET_NEXT(b))
        {
            if ((APR_BUCKET_IS_EOS(b) || AP_BUCKET_IS_EOR(b))
                && r->trailers_out && !apr_is_empty_table(r->trailers_out)) {
                h2_headers *headers;
                apr_table_t *trailers;
                
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c, APLOGNO(03049)
                              "h2_task(%s): sending trailers", task->id);
                trailers = apr_table_clone(r->pool, r->trailers_out);
                headers = h2_headers_rcreate(r, HTTP_OK, trailers, r->pool);
                e = h2_bucket_headers_create(bb->bucket_alloc, headers);
                APR_BUCKET_INSERT_BEFORE(b, e);
                apr_table_clear(r->trailers_out);
                ap_remove_output_filter(f);
                break;
            }
        }     
    }
     
    return ap_pass_brigade(f->next, bb);
}