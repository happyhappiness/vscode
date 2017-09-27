    b->type = &bucket_type_cgi;
    b->length = (apr_size_t)(-1);
    b->start = -1;

    /* Create the pollset */
    rv = apr_pollset_create(&data->pollset, 2, r->pool, 0);
    AP_DEBUG_ASSERT(rv == APR_SUCCESS);

    fd.desc_type = APR_POLL_FILE;
    fd.reqevents = APR_POLLIN;
    fd.p = r->pool;
    fd.desc.f = out; /* script's stdout */
    fd.client_data = (void *)1;
    rv = apr_pollset_add(data->pollset, &fd);
    AP_DEBUG_ASSERT(rv == APR_SUCCESS);

    fd.desc.f = err; /* script's stderr */
    fd.client_data = (void *)2;
    rv = apr_pollset_add(data->pollset, &fd);
    AP_DEBUG_ASSERT(rv == APR_SUCCESS);

    data->r = r;
    b->data = data;
    return b;
}

