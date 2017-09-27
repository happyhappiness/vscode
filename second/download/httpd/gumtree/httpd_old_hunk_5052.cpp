                APR_BRIGADE_CONCAT(bb, ctx->bb);
                break;
            }

            /* sanity check - data after completed compressed body and before eos? */
            if (ctx->done) {
                ap_log_rerror(
                        APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02482) "Encountered extra data after compressed data");
                return APR_EGENERAL;
            }

            /* read */
            apr_bucket_read(bkt, &data, &len, APR_BLOCK_READ);

