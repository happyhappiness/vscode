static int dumpio_input_filter (ap_filter_t *f, apr_bucket_brigade *bb,
    ap_input_mode_t mode, apr_read_type_e block, apr_off_t readbytes)
{

    apr_bucket *b;
    apr_status_t ret;
    conn_rec *c = f->c;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server,
        "mod_dumpio: %s [%s-%s] %" APR_OFF_T_FMT " readbytes",
         f->frec->name,
         whichmode(mode),
         ((block) == APR_BLOCK_READ) ? "blocking" : "nonblocking",
         readbytes) ;

    ret = ap_get_brigade(f->next, bb, mode, block, readbytes);

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