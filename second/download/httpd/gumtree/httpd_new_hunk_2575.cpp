            char buf[4096];
            const char *ip;
            apr_size_t bsize = sizeof(buf);
            apr_brigade_cleanup(tmpbb);
            if (APR_BRIGADE_EMPTY(bb)) {
                break;
            }
            rv = apr_brigade_split_line(tmpbb, bb,
                                        APR_BLOCK_READ, sizeof(buf));

            if (rv) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02076)
                             "Unable to read from file: %s", ctx->storage_path);
                return rv;
            }

            apr_brigade_flatten(tmpbb, buf, &bsize);
            if (bsize == 0) {
                break;
