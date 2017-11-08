static apr_status_t mmap_bucket_cleanup(void *data)
{
    /* the mmap has disappeared out from under us.  we have no choice
     * but to invalidate this bucket.  from now on, all you can do to this
     * bucket is destroy it, not read from it.
     */
    apr_bucket_mmap *m = data;

    m->mmap = NULL;
    return APR_SUCCESS;
}