static apr_status_t send_brigade_nonblocking(apr_socket_t *s,
                                             apr_bucket_brigade *bb,
                                             apr_size_t *bytes_written,
                                             conn_rec *c)
{
    apr_bucket *bucket, *next;
    apr_status_t rv;
    struct iovec vec[MAX_IOVEC_TO_WRITE];
    apr_size_t nvec = 0;

    remove_empty_buckets(bb);

    for (bucket = APR_BRIGADE_FIRST(bb);
         bucket != APR_BRIGADE_SENTINEL(bb);
         bucket = next) {
        next = APR_BUCKET_NEXT(bucket);
#if APR_HAS_SENDFILE
        if (APR_BUCKET_IS_FILE(bucket)) {
            apr_bucket_file *file_bucket = (apr_bucket_file *)(bucket->data);
            apr_file_t *fd = file_bucket->fd;
            /* Use sendfile to send this file unless:
             *   - the platform doesn't support sendfile,
             *   - the file is too small for sendfile to be useful, or
             *   - sendfile is disabled in the httpd config via "EnableSendfile off"
             */

            if ((apr_file_flags_get(fd) & APR_SENDFILE_ENABLED) &&
                (bucket->length >= AP_MIN_SENDFILE_BYTES)) {
                if (nvec > 0) {
                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 1);
                    rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
                    if (rv != APR_SUCCESS) {
                        (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
                        return rv;
                    }
                }
                rv = sendfile_nonblocking(s, bucket, bytes_written, c);
                if (nvec > 0) {
                    (void)apr_socket_opt_set(s, APR_TCP_NOPUSH, 0);
                    nvec = 0;
                }
                if (rv != APR_SUCCESS) {
                    return rv;
                }
                break;
            }
        }
#endif /* APR_HAS_SENDFILE */
        /* didn't sendfile */
        if (!APR_BUCKET_IS_METADATA(bucket)) {
            const char *data;
            apr_size_t length;
            
            /* Non-blocking read first, in case this is a morphing
             * bucket type. */
            rv = apr_bucket_read(bucket, &data, &length, APR_NONBLOCK_READ);
            if (APR_STATUS_IS_EAGAIN(rv)) {
                /* Read would block; flush any pending data and retry. */
                if (nvec) {
                    rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
                    if (rv) {
                        return rv;
                    }
                    nvec = 0;
                }
                
                rv = apr_bucket_read(bucket, &data, &length, APR_BLOCK_READ);
            }
            if (rv != APR_SUCCESS) {
                return rv;
            }

            /* reading may have split the bucket, so recompute next: */
            next = APR_BUCKET_NEXT(bucket);
            vec[nvec].iov_base = (char *)data;
            vec[nvec].iov_len = length;
            nvec++;
            if (nvec == MAX_IOVEC_TO_WRITE) {
                rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
                nvec = 0;
                if (rv != APR_SUCCESS) {
                    return rv;
                }
                break;
            }
        }
    }

    if (nvec > 0) {
        rv = writev_nonblocking(s, vec, nvec, bb, bytes_written, c);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    remove_empty_buckets(bb);

    return APR_SUCCESS;
}