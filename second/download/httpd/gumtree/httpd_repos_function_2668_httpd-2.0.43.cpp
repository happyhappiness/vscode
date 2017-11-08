static apr_status_t mmap_bucket_read(apr_bucket *b, const char **str, 
                                     apr_size_t *length, apr_read_type_e block)
{
    apr_bucket_mmap *m = b->data;
    apr_status_t ok;
    void *addr;
    
    if (!m->mmap) {
        /* due to cleanup issues we have no choice but to check this */
        return APR_EINVAL;
    }

    ok = apr_mmap_offset(&addr, m->mmap, b->start);
    if (ok != APR_SUCCESS) {
        return ok;
    }
    *str = addr;
    *length = b->length;
    return APR_SUCCESS;
}