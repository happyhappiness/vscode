static apr_status_t sendfile_nonblocking(apr_socket_t *s,
                                         apr_bucket *bucket,
                                         apr_size_t *cumulative_bytes_written,
                                         conn_rec *c)
{
    apr_status_t rv = APR_SUCCESS;
    apr_bucket_file *file_bucket;
    apr_file_t *fd;
    apr_size_t file_length;
    apr_off_t file_offset;
    apr_size_t bytes_written = 0;

    if (!APR_BUCKET_IS_FILE(bucket)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, c->base_server,
                     "core_filter: sendfile_nonblocking: "
                     "this should never happen");
        return APR_EGENERAL;
    }
    file_bucket = (apr_bucket_file *)(bucket->data);
    fd = file_bucket->fd;
    file_length = bucket->length;
    file_offset = bucket->start;

    if (bytes_written < file_length) {
        apr_size_t n = file_length - bytes_written;
        apr_status_t arv;
        apr_interval_time_t old_timeout;

        arv = apr_socket_timeout_get(s, &old_timeout);
        if (arv != APR_SUCCESS) {
            return arv;
        }
        arv = apr_socket_timeout_set(s, 0);
        if (arv != APR_SUCCESS) {
            return arv;
        }
        rv = apr_socket_sendfile(s, fd, NULL, &file_offset, &n, 0);
        if (rv == APR_SUCCESS) {
            bytes_written += n;
            file_offset += n;
        }
        arv = apr_socket_timeout_set(s, old_timeout);
        if ((arv != APR_SUCCESS) && (rv == APR_SUCCESS)) {
            rv = arv;
        }
    }
    if ((ap__logio_add_bytes_out != NULL) && (bytes_written > 0)) {
        ap__logio_add_bytes_out(c, bytes_written);
    }
    *cumulative_bytes_written += bytes_written;
    if ((bytes_written < file_length) && (bytes_written > 0)) {
        apr_bucket_split(bucket, bytes_written);
        APR_BUCKET_REMOVE(bucket);
        apr_bucket_destroy(bucket);
    }
    else if (bytes_written == file_length) {
        APR_BUCKET_REMOVE(bucket);
        apr_bucket_destroy(bucket);
    }
    return rv;
}