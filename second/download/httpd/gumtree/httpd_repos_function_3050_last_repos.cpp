static void *alloc_func(void *opaque, size_t size)
{
    return apr_bucket_alloc(size, opaque);
}