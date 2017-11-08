static apr_status_t transient_bucket_setaside(apr_bucket *b, apr_pool_t *pool)
{
    b = apr_bucket_heap_make(b, (char *)b->data + b->start, b->length, NULL);
    if (b == NULL) {
        return APR_ENOMEM;
    }
    return APR_SUCCESS;
}