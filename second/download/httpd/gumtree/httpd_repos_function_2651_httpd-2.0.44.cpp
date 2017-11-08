static apr_status_t pool_bucket_read(apr_bucket *b, const char **str, 
                                     apr_size_t *len, apr_read_type_e block)
{
    apr_bucket_pool *p = b->data;
    const char *base = p->base;

    if (p->pool == NULL) {
        /*
         * pool has been cleaned up... masquerade as a heap bucket from now
         * on. subsequent bucket operations will use the heap bucket code.
         */
        b->type = &apr_bucket_type_heap;
        base = p->heap.base;
    }
    *str = base + b->start;
    *len = b->length;
    return APR_SUCCESS;
}