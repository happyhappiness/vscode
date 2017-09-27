                /* bio_filter_out_flush() already passed down a flush bucket
                 * if there was any data to be flushed.
                 */
                apr_bucket_delete(bucket);
            }
        }
        else {
            /* filter output */
            const char *data;
            apr_size_t len;
            
            status = apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);

            if (!APR_STATUS_IS_EOF(status) && (status != APR_SUCCESS)) {
                break;
            }

            status = ssl_filter_write(f, data, len);
