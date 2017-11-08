static apr_bucket *cgi_bucket_create(request_rec *r,
                                     apr_file_t *out, apr_file_t *err,
                                     apr_bucket_alloc_t *list)
{
    apr_bucket *b = apr_bucket_alloc(sizeof(*b), list);
    apr_status_t rv;
    apr_pollfd_t fd;
    struct cgi_bucket_data *data = apr_palloc(r->pool, sizeof *data);
    
    APR_BUCKET_INIT(b);
    b->free = apr_bucket_free;
    b->list = list;
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