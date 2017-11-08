static void heap_bucket_destroy(void *data)
{
    apr_bucket_heap *h = data;

    if (apr_bucket_shared_destroy(h)) {
        (*h->free_func)(h->base);
        apr_bucket_free(h);
    }
}