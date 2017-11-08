static apr_status_t ssl_io_filter_Input(ap_filter_t *f,
                                        apr_bucket_brigade *bb,
                                        ap_input_mode_t mode,
                                        apr_read_type_e block,
                                        apr_off_t readbytes)
{
    apr_status_t status;
    ssl_io_input_ctx_t *ctx = f->ctx;

    apr_size_t len = sizeof(ctx->buffer);
    int is_init = (mode == AP_MODE_INIT);

    if (!ctx->inbio.ssl) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    /* XXX: we don't currently support anything other than these modes. */
    if (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE && 
        mode != AP_MODE_SPECULATIVE && mode != AP_MODE_INIT) {
        return APR_ENOTIMPL;
    }

    ctx->inbio.mode = mode;
    ctx->inbio.block = block;

    /* XXX: we could actually move ssl_hook_process_connection to an
     * ap_hook_process_connection but would still need to call it for
     * AP_MODE_INIT for protocols that may upgrade the connection
     * rather than have SSLEngine On configured.
     */
    status = ssl_hook_process_connection(ctx->frec);

    if (status != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status);
    }

    if (is_init) {
        /* protocol module needs to handshake before sending
         * data to client (e.g. NNTP or FTP)
         */
        return APR_SUCCESS;
    }

    if (ctx->inbio.mode == AP_MODE_READBYTES || 
        ctx->inbio.mode == AP_MODE_SPECULATIVE) {
        /* Protected from truncation, readbytes < MAX_SIZE_T 
         * FIXME: No, it's *not* protected.  -- jre */
        if (readbytes < len) {
            len = (apr_size_t)readbytes;
        }
        status = ssl_io_input_read(ctx, ctx->buffer, &len);
    }
    else if (ctx->inbio.mode == AP_MODE_GETLINE) {
        status = ssl_io_input_getline(ctx, ctx->buffer, &len);
    }
    else {
        /* We have no idea what you are talking about, so return an error. */
        return APR_ENOTIMPL;
    }

    if (status != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status);
    }

    if (len > 0) {
        apr_bucket *bucket =
            apr_bucket_transient_create(ctx->buffer, len, f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, bucket);
    }

    return APR_SUCCESS;
}