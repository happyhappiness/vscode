        else if (AP_BUCKET_IS_EOC(bucket)) {
            /* The special "EOC" bucket means a shutdown is needed;
             * - turn off buffering in bio_filter_out_write
             * - issue the SSL_shutdown
             */
            filter_ctx->nobuffer = 1;
            ssl_filter_io_shutdown(filter_ctx, f->c, 0);
            if ((status = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
                return status;
            }
            break;
        }
        else {
