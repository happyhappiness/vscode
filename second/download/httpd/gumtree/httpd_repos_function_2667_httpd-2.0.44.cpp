static apr_status_t mmap_bucket_cleanup(void *data)
{
    /* the apr_mmap_t is about to disappear out from under us, so we
     * have no choice but to pretend it doesn't exist anymore.  the
     * refcount is now useless because there's nothing to refer to
     * anymore.  so the only valid action on any remaining referrer
     * is to delete it.  no more reads, no more anything. */
    apr_bucket_mmap *m = data;

    m->mmap = NULL;
    return APR_SUCCESS;
}