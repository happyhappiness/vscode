                                         ap_input_mode_t mode,
                                         apr_read_type_e block,
                                         apr_off_t bytes)
{
    struct modssl_buffer_ctx *ctx = f->ctx;
    apr_status_t rv;
    apr_bucket *e, *d;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, f->c,
                  "read from buffered SSL brigade, mode %d, "
                  "%" APR_OFF_T_FMT " bytes",
                  mode, bytes);

