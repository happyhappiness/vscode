     * where we would end up with LOTS of zombies.
     */
    if (apr_pool_create(&sub_context, r->pool) != APR_SUCCESS)
        return -1;

    if ((rv = create_uncompress_child(&parm, sub_context, &pipe_out)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                    MODNAME ": couldn't spawn uncompress process: %s", r->uri);
        return -1;
    }

    *newch = (unsigned char *) apr_palloc(r->pool, n);
    rv = apr_file_read(pipe_out, *newch, &n);
    if (n == 0) {
        apr_pool_destroy(sub_context);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
            MODNAME ": read failed from uncompress of %s", r->filename);
        return -1;
    }
    apr_pool_destroy(sub_context);
    return n;
}
