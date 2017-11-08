static void terminate_headers(apr_bucket_alloc_t *bucket_alloc,
                              apr_bucket_brigade *header_brigade)
{
    apr_bucket *e;

    /* add empty line at the end of the headers */
    e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
}