static void free_func(void *opaque, void *block)
{
    if (block) {
        apr_bucket_free(block);
    }
}