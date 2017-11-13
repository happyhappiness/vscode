static apr_status_t ssl_filter_write(ap_filter_t *f,
                                     const char *data,
                                     apr_size_t len)
{
    SSLFilterRec *ctx = f->ctx;
    apr_size_t n;

    /* write SSL */
    n = ssl_io_hook_write(ctx->pssl, (unsigned char *)data, len);

    if (n != len) {
        conn_rec *c = f->c;
        char *reason = "reason unknown";

        /* XXX: probably a better way to determine this */
        if (SSL_total_renegotiations(ctx->pssl)) {
            reason = "likely due to failed renegotiation";
        }

        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                "failed to write %d of %d bytes (%s)",
                n > 0 ? len - n : len, len, reason);

        return APR_EINVAL;
    }

    return APR_SUCCESS;
}