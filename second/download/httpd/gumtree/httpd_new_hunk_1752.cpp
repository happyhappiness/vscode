    if ((sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE) &&
        !sslconn->client_cert)
    {
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                      "No acceptable peer certificate available");

        ssl_filter_io_shutdown(filter_ctx, c, 1);
        return APR_ECONNABORTED;
    }

    return APR_SUCCESS;
}

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
