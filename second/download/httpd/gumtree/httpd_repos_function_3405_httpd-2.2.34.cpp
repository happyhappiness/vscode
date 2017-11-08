static apr_status_t socket_bucket_read(apr_bucket *a, const char **str,
                                       apr_size_t *len, apr_read_type_e block)
{
    apr_socket_t *p = a->data;
    char *buf;
    apr_status_t rv;
    apr_interval_time_t timeout;

    if (block == APR_NONBLOCK_READ) {
        apr_socket_timeout_get(p, &timeout);
        apr_socket_timeout_set(p, 0);
    }

    *str = NULL;
    *len = APR_BUCKET_BUFF_SIZE;
    buf = apr_bucket_alloc(*len, a->list); /* XXX: check for failure? */

    rv = apr_socket_recv(p, buf, len);

    if (block == APR_NONBLOCK_READ) {
        apr_socket_timeout_set(p, timeout);
    }

    if (rv != APR_SUCCESS && rv != APR_EOF) {
        apr_bucket_free(buf);
        return rv;
    }
    /*
     * If there's more to read we have to keep the rest of the socket
     * for later. XXX: Note that more complicated bucket types that
     * refer to data not in memory and must therefore have a read()
     * function similar to this one should be wary of copying this
     * code because if they have a destroy function they probably
     * want to migrate the bucket's subordinate structure from the
     * old bucket to a raw new one and adjust it as appropriate,
     * rather than destroying the old one and creating a completely
     * new bucket.
     *
     * Even if there is nothing more to read, don't close the socket here
     * as we have to use it to send any response :)  We could shut it 
     * down for reading, but there is no benefit to doing so.
     */
    if (*len > 0) {
        apr_bucket_heap *h;
        /* Change the current bucket to refer to what we read */
        a = apr_bucket_heap_make(a, buf, *len, apr_bucket_free);
        h = a->data;
        h->alloc_len = APR_BUCKET_BUFF_SIZE; /* note the real buffer size */
        *str = buf;
        APR_BUCKET_INSERT_AFTER(a, apr_bucket_socket_create(p, a->list));
    }
    else {
        apr_bucket_free(buf);
        a = apr_bucket_immortal_make(a, "", 0);
        *str = a->data;
    }
    return APR_SUCCESS;
}