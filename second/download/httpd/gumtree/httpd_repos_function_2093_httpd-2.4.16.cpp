static int ap_proxy_clear_connection(request_rec *r, apr_table_t *headers)
{
    const char **name;
    header_connection x;

    x.pool = r->pool;
    x.array = NULL;
    x.first = NULL;
    x.closed = 0;

    apr_table_unset(headers, "Proxy-Connection");

    apr_table_do(find_conn_headers, &x, headers, "Connection", NULL);
    if (x.first) {
        /* fast path - no memory allocated for one header */
        apr_table_unset(headers, "Connection");
        apr_table_unset(headers, x.first);
    }
    if (x.array) {
        /* two or more headers */
        while ((name = apr_array_pop(x.array))) {
            apr_table_unset(headers, *name);
        }
    }

    return x.closed;
}