static apr_status_t bucket_socket_ex_read(apr_bucket *a, const char **str,
                                          apr_size_t *len,
                                          apr_read_type_e block)
{
    socket_ex_data *data = a->data;
    apr_socket_t *p = data->sock;
    char *buf;
    apr_status_t rv;
    apr_interval_time_t timeout;

    if (block == APR_NONBLOCK_READ) {
        apr_socket_timeout_get(p, &timeout);
        apr_socket_timeout_set(p, 0);
    }

    *str = NULL;
    *len = APR_BUCKET_BUFF_SIZE;
    buf = apr_bucket_alloc(*len, a->list);

    rv = apr_socket_recv(p, buf, len);

    if (block == APR_NONBLOCK_READ) {
        apr_socket_timeout_set(p, timeout);
    }

    if (rv != APR_SUCCESS && rv != APR_EOF) {
        apr_bucket_free(buf);
        return rv;
    }

    if (*len > 0) {
        apr_bucket_heap *h;

        /* count for stats */
        *data->counter += *len;

        /* Change the current bucket to refer to what we read */
        a = apr_bucket_heap_make(a, buf, *len, apr_bucket_free);
        h = a->data;
        h->alloc_len = APR_BUCKET_BUFF_SIZE; /* note the real buffer size */
        *str = buf;
        APR_BUCKET_INSERT_AFTER(a, bucket_socket_ex_create(data, a->list));
    }
    else {
        apr_bucket_free(buf);
        a = apr_bucket_immortal_make(a, "", 0);
        *str = a->data;
    }
    return APR_SUCCESS;
}