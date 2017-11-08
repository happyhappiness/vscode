apr_status_t apr_dir_read(apr_finfo_t *finfo, apr_int32_t wanted,
                          apr_dir_t *thedir)
{
    apr_status_t ret = 0;
#if APR_HAS_THREADS && defined(_POSIX_THREAD_SAFE_FUNCTIONS) \
    && !defined(READDIR_IS_THREAD_SAFE)
    struct dirent *retent;

    ret = readdir_r(thedir->dirstruct, thedir->entry, &retent);

    /* Avoid the Linux problem where at end-of-directory thedir->entry
     * is set to NULL, but ret = APR_SUCCESS.
     */
    if(!ret && thedir->entry != retent)
        ret = APR_ENOENT;
#else
    /* We're about to call a non-thread-safe readdir() that may
       possibly set `errno', and the logic below actually cares about
       errno after the call.  Therefore we need to clear errno first. */
    errno = 0;
    thedir->entry = readdir(thedir->dirstruct);
    if (thedir->entry == NULL) {
        /* If NULL was returned, this can NEVER be a success. Can it?! */
        if (errno == APR_SUCCESS) {
            ret = APR_ENOENT;
        }
        else
            ret = errno;
    }
#endif

    /* No valid bit flag to test here - do we want one? */
    finfo->fname = NULL;

    if (ret) {
        finfo->valid = 0;
        return ret;
    }

    /* What we already know - and restrict the wanted test below to stat
     * only if stat will give us what this platform supports, and we can't
     * get it from the platform.
     * XXX: Optimize here with d_fileno, d_type etc by platform */
    wanted &= ~(APR_FINFO_NAME);
    if (wanted)
    {
        char fspec[APR_PATH_MAX];
        int off;
        apr_cpystrn(fspec, thedir->dirname, sizeof(fspec));
        off = strlen(fspec);
        if (fspec[off - 1] != '/')
            fspec[off++] = '/';
        apr_cpystrn(fspec + off, thedir->entry->d_name, sizeof(fspec) - off);
        ret = apr_lstat(finfo, fspec, wanted, thedir->pool);
    }

    if (wanted && (ret == APR_SUCCESS || ret == APR_INCOMPLETE)) {
        wanted &= ~finfo->valid;
        ret = APR_SUCCESS;
    }
    else {
        /* We don't bail because we fail to stat, when we are only -required-
         * to readdir... but the result will be APR_INCOMPLETE
         */
        finfo->pool = thedir->pool;
        finfo->valid = 0;
    }

    /* We passed a stack name that is now gone */
    finfo->fname = NULL;
    finfo->valid |= APR_FINFO_NAME;
    /* XXX: Optimize here with d_fileno, d_type etc by platform */
    finfo->name = thedir->entry->d_name;

    if (wanted)
        return APR_INCOMPLETE;

    return APR_SUCCESS;
}