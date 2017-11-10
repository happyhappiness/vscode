static apr_status_t alloc_cleanup(void *data)
{
    apr_bucket_alloc_t *list = data;
    apr_allocator_t *allocator = list->allocator;

    apr_allocator_free(allocator, list->blocks);
    apr_allocator_destroy(allocator);
    return APR_SUCCESS;
}