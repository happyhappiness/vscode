static apr_status_t alloc_cleanup(void *data)
{
    apr_bucket_alloc_t *list = data;

    apr_allocator_free(list->allocator, list->blocks);

#if APR_POOL_DEBUG
    if (list->pool && list->allocator != apr_pool_allocator_get(list->pool)) {
        apr_allocator_destroy(list->allocator);
    }
#endif

    return APR_SUCCESS;
}