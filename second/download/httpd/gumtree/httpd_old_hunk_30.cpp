
            /* NEVER save an EOS in here.  If we are saving a brigade with
             * an EOS bucket, then we are doing keepalive connections, and
             * we want to process to second request fully.
             */
            if (APR_BUCKET_IS_EOS(last_e)) {
                apr_bucket *bucket = NULL;
                /* If we are in here, then this request is a keepalive.  We
                 * need to be certain that any data in a bucket is valid
                 * after the request_pool is cleared.
                 */
                if (ctx->b == NULL) {
                    ctx->b = apr_brigade_create(net->c->pool,
                                                net->c->bucket_alloc);
                }

                APR_BRIGADE_FOREACH(bucket, b) {
                    const char *str;
                    apr_size_t n;

                    rv = apr_bucket_read(bucket, &str, &n, APR_BLOCK_READ);

                    /* This apr_brigade_write does not use a flush function
                       because we assume that we will not write enough data
                       into it to cause a flush. However, if we *do* write
                       "too much", then we could end up with transient
                       buckets which would suck. This works for now, but is
                       a bit shaky if changes are made to some of the
                       buffering sizes. Let's do an assert to prevent
                       potential future problems... */
                    AP_DEBUG_ASSERT(AP_MIN_BYTES_TO_WRITE <=
                                    APR_BUCKET_BUFF_SIZE);
                    if (rv != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, c->base_server,
                                     "core_output_filter: Error reading from bucket.");
                        return HTTP_INTERNAL_SERVER_ERROR;
                    }

                    apr_brigade_write(ctx->b, NULL, NULL, str, n);
                }

                apr_brigade_destroy(b);
            }
            else {
                ap_save_brigade(f, &ctx->b, &b, c->pool);
            }

            return APR_SUCCESS;
        }

        if (fd) {
            apr_hdtr_t hdtr;
