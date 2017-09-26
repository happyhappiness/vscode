             * - turn off buffering in bio_filter_out_write
             * - issue the SSL_shutdown
             */
            filter_ctx->nobuffer = 1;
            status = ssl_filter_io_shutdown(filter_ctx, f->c, 0);
            if (status != APR_SUCCESS) {
                ap_log_cerror(APLOG_MARK, APLOG_INFO, status, f->c,
                              "SSL filter error shutting down I/O");
            }
            if ((status = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
                return status;
            }
            break;
        }
        else {
            /* filter output */
            const char *data;
            apr_size_t len;

            status = apr_bucket_read(bucket, &data, &len, rblock);

            if (APR_STATUS_IS_EAGAIN(status)) {
                /* No data available: flush... */
                if (bio_filter_out_flush(filter_ctx->pbioWrite) < 0) {
                    status = outctx->rc;
