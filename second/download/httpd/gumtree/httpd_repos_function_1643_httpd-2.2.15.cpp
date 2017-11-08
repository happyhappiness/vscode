static void filter_trace(conn_rec *c, int debug, const char *fname,
                         apr_bucket_brigade *bb)
{
    apr_bucket *b;

    switch (debug) {
    case 0:        /* normal, operational use */
        return;
    case 1:        /* mod_diagnostics level */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, "%s", fname);
        for (b = APR_BRIGADE_FIRST(bb);
             b != APR_BRIGADE_SENTINEL(bb);
             b = APR_BUCKET_NEXT(b)) {

            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                          "%s: type: %s, length: %" APR_SIZE_T_FMT,
                          fname, b->type->name ? b->type->name : "(unknown)",
                          b->length);
        }
        break;
    }
}