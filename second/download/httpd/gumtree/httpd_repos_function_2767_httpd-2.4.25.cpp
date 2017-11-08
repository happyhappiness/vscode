apr_bucket *h2_bucket_headers_beam(struct h2_bucket_beam *beam,
                                    apr_bucket_brigade *dest,
                                    const apr_bucket *src)
{
    if (H2_BUCKET_IS_HEADERS(src)) {
        h2_headers *r = ((h2_bucket_headers *)src->data)->headers;
        apr_bucket *b = h2_bucket_headers_create(dest->bucket_alloc, r);
        APR_BRIGADE_INSERT_TAIL(dest, b);
        return b;
    }
    return NULL;
}