                /* bio_filter_out_flush() already passed down a flush bucket
                 * if there was any data to be flushed.
                 */
                apr_bucket_delete(bucket);
            }
        }
        else if (AP_BUCKET_IS_EOC(bucket)) {
            /* The special "EOC" bucket means a shutdown is needed;
             * - turn off buffering in bio_filter_out_write
             * - issue the SSL_shutdown
             */
            filter_ctx->nobuffer = 1;
            status = ssl_filter_io_shutdown(filter_ctx, f->c, 0);
            if (status != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_INFO, status, NULL,
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
                    break;
                }
                rblock = APR_BLOCK_READ;
                continue; /* and try again with a blocking read. */
            }

            rblock = APR_NONBLOCK_READ;

            if (!APR_STATUS_IS_EOF(status) && (status != APR_SUCCESS)) {
                break;
            }

            status = ssl_filter_write(f, data, len);
