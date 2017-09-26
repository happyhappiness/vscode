    apr_bucket *e;
    apr_off_t cl_val = 0;
    apr_off_t bytes;
    apr_off_t bytes_streamed = 0;

    if (old_cl_val) {
        add_cl(p, bucket_alloc, header_brigade, old_cl_val);
        if (APR_SUCCESS != (status = apr_strtoff(&cl_val, old_cl_val, NULL,
                                                 0))) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }
    terminate_headers(bucket_alloc, header_brigade);

    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
    {
