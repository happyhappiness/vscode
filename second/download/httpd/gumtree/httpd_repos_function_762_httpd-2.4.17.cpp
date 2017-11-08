static apr_status_t ssl_io_filter_input(ap_filter_t *f,
                                        apr_bucket_brigade *bb,
                                        ap_input_mode_t mode,
                                        apr_read_type_e block,
                                        apr_off_t readbytes)
{
    apr_status_t status;
    bio_filter_in_ctx_t *inctx = f->ctx;
    const char *start = inctx->buffer; /* start of block to return */
    apr_size_t len = sizeof(inctx->buffer); /* length of block to return */
    int is_init = (mode == AP_MODE_INIT);

    if (f->c->aborted) {
        /* XXX: Ok, if we aborted, we ARE at the EOS.  We also have
         * aborted.  This 'double protection' is probably redundant,
         * but also effective against just about anything.
         */
        apr_bucket *bucket = apr_bucket_eos_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, bucket);
        return APR_ECONNABORTED;
    }

    if (!inctx->ssl) {
        SSLConnRec *sslconn = myConnConfig(f->c);
        if (sslconn->non_ssl_request == NON_SSL_SEND_HDR_SEP) {
            apr_bucket *bucket = apr_bucket_immortal_create(CRLF, 2, f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, bucket);
            sslconn->non_ssl_request = NON_SSL_SET_ERROR_MSG;
            return APR_SUCCESS;
        }
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    /* XXX: we don't currently support anything other than these modes. */
    if (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE &&
        mode != AP_MODE_SPECULATIVE && mode != AP_MODE_INIT) {
        return APR_ENOTIMPL;
    }

    inctx->mode = mode;
    inctx->block = block;

    /* XXX: we could actually move ssl_io_filter_handshake to an
     * ap_hook_process_connection but would still need to call it for
     * AP_MODE_INIT for protocols that may upgrade the connection
     * rather than have SSLEngine On configured.
     */
    if ((status = ssl_io_filter_handshake(inctx->filter_ctx)) != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status);
    }

    if (is_init) {
        /* protocol module needs to handshake before sending
         * data to client (e.g. NNTP or FTP)
         */
        return APR_SUCCESS;
    }

    if (inctx->mode == AP_MODE_READBYTES ||
        inctx->mode == AP_MODE_SPECULATIVE) {
        /* Protected from truncation, readbytes < MAX_SIZE_T
         * FIXME: No, it's *not* protected.  -- jre */
        if (readbytes < len) {
            len = (apr_size_t)readbytes;
        }
        status = ssl_io_input_read(inctx, inctx->buffer, &len);
    }
    else if (inctx->mode == AP_MODE_GETLINE) {
        const char *pos;

        /* Satisfy the read directly out of the buffer if possible;
         * invoking ssl_io_input_getline will mean the entire buffer
         * is copied once (unnecessarily) for each GETLINE call. */
        if (inctx->cbuf.length
            && (pos = memchr(inctx->cbuf.value, APR_ASCII_LF,
                             inctx->cbuf.length)) != NULL) {
            start = inctx->cbuf.value;
            len = 1 + pos - start; /* +1 to include LF */
            /* Buffer contents now consumed. */
            inctx->cbuf.value += len;
            inctx->cbuf.length -= len;
            status = APR_SUCCESS;
        }
        else {
            /* Otherwise fall back to the hard way. */
            status = ssl_io_input_getline(inctx, inctx->buffer, &len);
        }
    }
    else {
        /* We have no idea what you are talking about, so return an error. */
        status = APR_ENOTIMPL;
    }

    /* It is possible for mod_ssl's BIO to be used outside of the
     * direct control of mod_ssl's input or output filter -- notably,
     * when mod_ssl initiates a renegotiation.  Switching the BIO mode
     * back to "blocking" here ensures such operations don't fail with
     * SSL_ERROR_WANT_READ. */
    inctx->block = APR_BLOCK_READ;

    /* Handle custom errors. */
    if (status != APR_SUCCESS) {
        return ssl_io_filter_error(f, bb, status);
    }

    /* Create a transie