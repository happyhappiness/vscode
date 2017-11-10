static apr_status_t xml2enc_filter(request_rec* r, const char* enc,
                                   unsigned int mode)
{
    /* set up a ready-initialised ctx to convert to enc, and insert filter */
    apr_xlate_t* convset; 
    apr_status_t rv;
    unsigned int flags = (mode ^ ENCIO);
    if ((mode & ENCIO) == ENCIO_OUTPUT) {
        rv = apr_xlate_open(&convset, enc, "UTF-8", r->pool);
        flags |= ENC_INITIALISED;
    }
    else if ((mode & ENCIO) == ENCIO_INPUT) {
        rv = apr_xlate_open(&convset, "UTF-8", enc, r->pool);
        flags |= ENC_INITIALISED;
    }
    else if ((mode & ENCIO) == ENCIO_INPUT_CHECKS) {
        convset = NULL;
        rv = APR_SUCCESS; /* we'll initialise later by sniffing */
    }
    else {
        rv = APR_EGENERAL;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01426)
                      "xml2enc: bad mode %x", mode);
    }
    if (rv == APR_SUCCESS) {
        xml2ctx* ctx = apr_pcalloc(r->pool, sizeof(xml2ctx));
        ctx->flags = flags;
        if (flags & ENC_INITIALISED) {
            ctx->convset = convset;
            ctx->bblen = BUFLEN;
            ctx->buf = apr_palloc(r->pool, (apr_size_t)ctx->bblen);
        }
        ap_add_output_filter("xml2enc", ctx, r, r->connection);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01427)
                      "xml2enc: Charset %s not supported.", enc) ;
    }
    return rv;
}