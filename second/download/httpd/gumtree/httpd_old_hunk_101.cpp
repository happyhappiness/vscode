
      default:
        return status;
    }

    APR_BRIGADE_INSERT_TAIL(bb, bucket);

    return APR_SUCCESS;
}

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

static void ssl_io_input_add_filter(SSLFilterRec *frec, conn_rec *c,
                                    SSL *ssl)
{
    ssl_io_input_ctx_t *ctx;

    ctx = apr_palloc(c->pool, sizeof(*ctx));

    frec->pInputFilter = ap_add_input_filter(ssl_io_filter, ctx, NULL, c);

    frec->pbioRead = BIO_new(BIO_s_in_bucket());
    frec->pbioRead->ptr = (void *)&ctx->inbio;

    ctx->frec = frec;
    ctx->inbio.ssl = ssl;
    ctx->inbio.wbio = frec->pbioWrite;
    ctx->inbio.f = frec->pInputFilter;
    ctx->inbio.bb = apr_brigade_create(c->pool, c->bucket_alloc);
    ctx->inbio.bucket = NULL;
    ctx->inbio.cbuf.length = 0;

    ctx->cbuf.length = 0;

    ctx->pool = c->pool;
}

static apr_status_t ssl_io_filter_cleanup (void *data)
{
    apr_status_t ret;
    SSLFilterRec *pRec = (SSLFilterRec *)data;

    if (!pRec->pssl) {
        /* already been shutdown */
        return APR_SUCCESS;
    }

    if ((ret = ssl_hook_CloseConnection(pRec)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, ret, NULL,
                     "Error in ssl_hook_CloseConnection");
    }

    return ret;
}

void ssl_io_filter_init(conn_rec *c, SSL *ssl)
{
    SSLFilterRec *filter;

    filter = apr_palloc(c->pool, sizeof(SSLFilterRec));

    filter->pOutputFilter   = ap_add_output_filter(ssl_io_filter,
                                                   filter, NULL, c);

    filter->pbioWrite       = BIO_new(BIO_s_bucket());
    filter->pbioWrite->ptr  = (void *)BIO_bucket_new(filter, c);

    ssl_io_input_add_filter(filter, c, ssl);

    SSL_set_bio(ssl, filter->pbioRead, filter->pbioWrite);
    filter->pssl            = ssl;

    apr_pool_cleanup_register(c->pool, (void*)filter,
                              ssl_io_filter_cleanup, apr_pool_cleanup_null);

    if (c->base_server->loglevel >= APLOG_DEBUG) {
        BIO_set_callback(SSL_get_rbio(ssl), ssl_io_data_cb);
        BIO_set_callback_arg(SSL_get_rbio(ssl), (void *)ssl);
    }

    return;
}

void ssl_io_filter_register(apr_pool_t *p)
{
    ap_register_input_filter  (ssl_io_filter, ssl_io_filter_Input,  NULL, AP_FTYPE_CONNECTION + 5);
    ap_register_output_filter (ssl_io_filter, ssl_io_filter_Output, NULL, AP_FTYPE_CONNECTION + 5);
    return;
}

/*  _________________________________________________________________
**
**  I/O Data Debugging
