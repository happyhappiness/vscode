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

