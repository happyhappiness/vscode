h2_headers *h2_bucket_headers_get(apr_bucket *b)
{
    if (H2_BUCKET_IS_HEADERS(b)) {
        return ((h2_bucket_headers *)b->data)->headers;
    }
    return NULL;
}