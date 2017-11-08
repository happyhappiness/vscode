apr_status_t apr_dir_read(apr_finfo_t *finfo, apr_int32_t wanted,
                          apr_dir_t *thedir)
{
    apr_status_t ret = 0;
#ifdef DIRENT_TYPE
    apr_filetype_e type;
#endif
#if APR_HAS_THREADS && defined(_POSIX_THREAD_SAFE_FUNCTIONS) \
                    && !defined(READDIR_IS_THREAD_SAFE)
    struct dirent *retent;

    ret = readdir_r(thedir->dirstruct, thedir->entry, &retent);

    /* Avoid the Linux problem where at end-of-directory thedir->entry
     * is set to NULL, but ret = APR_SUCCESS.
     */
    if(!ret && thedir->entry != retent)
        ret = APR_ENOENT;

    /* Solaris is a bit strange, if there are no more entries in the
     * directory, it returns EINVAL.  Since this is against POSIX, we
     * hack around the problem here.  EINVAL is possible from other
     * readdir implementations, but only if the result buffer is too small.
     * since we control the size of that buffer, we should never have
     * that problem.
     */
    if (ret == EINVAL) {
        ret = ENOENT;
    }
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

#ifdef DIRENT_TYPE
    type = filetype_from_dirent_type(thedir->entry->DIRENT_TYPE);
    if (type != APR_UNKFILE) {
        wanted &= ~APR_FINFO_TYPE;
    }
#endif
#ifdef DIRENT_INODE
    if (thedir->entry->DIRENT_INODE && thedir->entry->DIRENT_INODE != -1) {
        wanted &= ~APR_FINFO_INODE;
    }
#endif

    wanted &= ~APR_FINFO_NAME;

    if (wanted)
    {
        char fspec[APR_PATH_MAX];
        int off;
        apr_cpystrn(fspec, thedir->dirname, sizeof(fspec));
        off = strlen(fspec);
        if ((fspec[off - 1] != '/') && (off + 1 < sizeof(fspec)))
            fspec[off++] = '/';
        apr_cpystrn(fspec + off, thedir->entry->d_name, sizeof(fspec) - off);
        ret = apr_lstat(finfo, fspec, wanted, thedir->pool);
        /* We passed a stack name that will disappear */
        finfo->fname = NULL;
    }

    if (wanted && (ret == APR_SUCCESS || ret == APR_INCOMPLETE)) {
        wanted &= ~finfo->valid;
    }
    else {
        /* We don't bail because we fail to stat, when we are only -required-
         * to readdir... but the result will be APR_INCOMPLETE
         */
        finfo->pool = thedir->pool;
        finfo->valid = 0;
#ifdef DIRENT_TYPE
        if (type != APR_UNKFILE) {
            finfo->filetype = type;
            finfo->valid |= APR_FINFO_TYPE;
        }
#endif
#ifdef DIRENT_INODE
        if (thedir->entry->DIRENT_INODE && thedir->entry->DIRENT_INODE != -1) {
            finfo->inode = thedir->entry->DIRENT_INODE;
            finfo->valid |= APR_FINFO_INODE;
        }
#endif
    }

    finfo->name = apr_pstrdup(thedir->pool, thedir->entry->d_name);
    finfo->valid |= APR_FINFO_NAME;

    if (wanted)
        return APR_INCOMPLETE;

    return APR_SUCCESS;
}