
    if (ret == APR_SUCCESS) {
        for (b = APR_BRIGADE_FIRST(bb); b != APR_BRIGADE_SENTINEL(bb); b = APR_BUCKET_NEXT(b)) {
          dumpit(f, b);
        }
    } else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server,
        "mod_dumpio: %s - %d", f->frec->name, ret) ;
    }

    return APR_SUCCESS ;
}

static int dumpio_output_filter (ap_filter_t *f, apr_bucket_brigade *bb)
{
    apr_bucket *b;
    conn_rec *c = f->c;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server, "mod_dumpio: %s", f->frec->name) ;

    for (b = APR_BRIGADE_FIRST(bb); b != APR_BRIGADE_SENTINEL(bb); b = APR_BUCKET_NEXT(b)) {
        /*
         * If we ever see an EOS, make sure to FLUSH.
         */
        if (APR_BUCKET_IS_EOS(b)) {
