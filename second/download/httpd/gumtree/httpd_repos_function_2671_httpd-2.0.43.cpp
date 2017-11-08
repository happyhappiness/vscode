static apr_status_t mmap_bucket_setaside(apr_bucket *data, apr_pool_t *p)
{
    apr_bucket_mmap *m = data->data;
    apr_mmap_t *mm = m->mmap;
    apr_mmap_t *new_mm;
    apr_status_t ok;

    if (!mm) {
        /* due to cleanup issues we have no choice but to check this */
        return APR_EINVAL;
    }

    if (apr_pool_is_ancestor(mm->cntxt, p)) {
        return APR_SUCCESS;
    }

    ok = apr_mmap_dup(&new_mm, mm, p, 1);
    if (ok != APR_SUCCESS) {
        return ok;
    }
    
    m->mmap = new_mm;
    if (new_mm->is_owner) {
        apr_pool_cleanup_kill(mm->cntxt, m, mmap_bucket_cleanup);
        apr_pool_cleanup_register(new_mm->cntxt, m, mmap_bucket_cleanup,
                                  apr_pool_cleanup_null);
    }

    return APR_SUCCESS;
}