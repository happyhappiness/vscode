static apr_status_t pool_bucket_cleanup(void *data)
{
    apr_bucket_pool *p = data;

    /*
     * If the pool gets cleaned up, we have to copy the data out
     * of the pool and onto the heap.  But the apr_buckets out there
     * that point to this pool bucket need to be notified such that
     * they can morph themselves into a regular heap bucket the next
     * time they try to read.  To avoid having to manipulate
     * reference counts and b->data pointers, the apr_bucket_pool
     * actually _contains_ an apr_bucket_heap as its first element,
     * so the two share their apr_bucket_refcount member, and you
     * can typecast a pool bucket struct to make it look like a
     * regular old heap bucket struct.
     */
    p->heap.base = apr_bucket_alloc(p->heap.alloc_len, p->list);
    memcpy(p->heap.base, p->base, p->heap.alloc_len);
    p->base = NULL;
    p->pool = NULL;

    return APR_SUCCESS;
}