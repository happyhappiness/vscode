                                         apr_read_type_e block,
                                         apr_off_t bytes)
{
    struct modssl_buffer_ctx *ctx = f->ctx;
    apr_status_t rv;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                  "read from buffered SSL brigade, mode %d, "
                  "%" APR_OFF_T_FMT " bytes",
                  mode, bytes);

    if (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE) {
        return APR_ENOTIMPL;
