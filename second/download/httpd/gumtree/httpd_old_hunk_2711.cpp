    apr_bucket *fb;
    int do_sleep = 0;
    apr_bucket_alloc_t *ba = f->r->connection->bucket_alloc;
    apr_bucket_brigade *bb = input_bb;

    if (f->c->aborted) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, "rl: conn aborted");
        apr_brigade_cleanup(bb);
        return APR_ECONNABORTED;
    }

    if (ctx == NULL) {

