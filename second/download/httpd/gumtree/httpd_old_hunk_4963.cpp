                /* Move everything to the returning brigade. */
                APR_BUCKET_REMOVE(bkt);
                APR_BRIGADE_CONCAT(bb, ctx->bb);
                break;
            }

            /* read */
            apr_bucket_read(bkt, &data, &len, APR_BLOCK_READ);

            /* pass through zlib inflate. */
            ctx->stream.next_in = (unsigned char *)data;
            ctx->stream.avail_in = len;
