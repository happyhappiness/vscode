static apr_status_t file_dup(apr_file_t **new_file, apr_file_t *old_file, apr_pool_t *p)
{
    int rv;
    apr_file_t *dup_file;

    if (*new_file == NULL) {
        dup_file = (apr_file_t *)apr_palloc(p, sizeof(apr_file_t));

        if (dup_file == NULL) {
            return APR_ENOMEM;
        }

        dup_file->filedes = -1;
    } else {
      dup_file = *new_file;
    }

    dup_file->pool = p;
    rv = DosDupHandle(old_file->filedes, &dup_file->filedes);

    if (rv) {
        return APR_FROM_OS_ERROR(rv);
    }

    dup_file->fname = apr_pstrdup(dup_file->pool, old_file->fname);
    dup_file->buffered = old_file->buffered;
    dup_file->isopen = old_file->isopen;
    dup_file->flags = old_file->flags & ~APR_INHERIT;
    /* TODO - dup pipes correctly */
    dup_file->pipe = old_file->pipe;

    if (*new_file == NULL) {
        apr_pool_cleanup_register(dup_file->pool, dup_file, apr_file_cleanup,
                            apr_pool_cleanup_null);
        *new_file = dup_file;
    }

    return APR_SUCCESS;
}