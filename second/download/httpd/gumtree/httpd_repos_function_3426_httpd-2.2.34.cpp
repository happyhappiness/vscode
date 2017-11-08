static apr_status_t mmap_bucket_setaside(apr_bucket *b, apr_pool_t *p)
{
    apr_bucket_mmap *m = b->data;
    apr_mmap_t *mm = m->mmap;
    apr_mmap_t *new_mm;
    apr_status_t ok;

    if (!mm) {
        /* the apr_mmap_t was already cleaned up out from under us */
        return APR_EINVAL;
    }

    /* shortcut if possible */
    if (apr_pool_is_ancestor(mm->cntxt, p)) {
        return APR_SUCCESS;
    }

    /* duplicate apr_mmap_t into new pool */
    ok = apr_mmap_dup(&new_mm, mm, p);
    if (ok != APR_SUCCESS) {
        return ok;
    }

    /* decrement refcount on old apr_bucket_mmap */
    mmap_bucket_destroy(m);

    /* create new apr_bucket_mmap pointing to new apr_mmap_t */
    apr_bucket_mmap_make(b, new_mm, b->start, b->length);

    return APR_SUCCESS;
}