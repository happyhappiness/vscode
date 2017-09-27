
            if (APR_BUCKET_IS_EOS(e)) {
                eos = 1;
            } else if (!APR_BUCKET_IS_METADATA(e)) {
                rv = apr_bucket_read(e, &data, &len, APR_BLOCK_READ);
                if (rv != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02016)
                                  "could not read bucket for SSL buffer");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                total += len;
            }

            rv = apr_bucket_setaside(e, r->pool);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02017)
                              "could not setaside bucket for SSL buffer");
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
