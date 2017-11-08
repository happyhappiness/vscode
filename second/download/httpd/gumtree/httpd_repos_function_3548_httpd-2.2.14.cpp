apr_status_t apr_dir_read(apr_finfo_t *finfo, apr_int32_t wanted,
                          apr_dir_t *thedir)
{
    apr_status_t ret = 0;
#ifdef DIRENT_TYPE
    apr_filetype_e type;
#endif
#if APR_HAS_THREADS && defined(_POSIX_THREAD_SAFE_FUNCTIONS) \
                    && !defined(READDIR_IS_THREAD_SAFE)
#ifdef APR_USE_READDIR64_R
    struct dirent64 *retent;

    /* If LFS is enabled and readdir64_r is available, readdir64_r is
     * used in preference to readdir_r.  This allows directories to be
     * read which contain a (64-bit) inode number which doesn't fit
     * into the 32-bit apr_ino_t, iff the caller doesn't actually care
     * about the inode number (i.e. wanted & APR_FINFO_INODE == 0).
     * (such inodes may be seen in some wonky NFS environments)
     *
     * Similarly, if the d_off field cannot be reprented in a 32-bit
     * offset, the libc readdir_r() would barf; using readdir64_r
     * bypasses that case entirely since APR does not care about
     * d_off. */

    ret = readdir64_r(thedir->dirstruct, thedir->entry, &retent);
#else

    struct dirent *retent;

    ret = readdir_r(thedir->dirstruct, thedir->entry, &retent);
#endif

    /* POSIX treats "end of directory" as a non-error case, so ret
     * will be zero and retent will be set to NULL in that case. */
    if (!ret && retent == NULL) {
        ret = APR_ENOENT;
    }

    /* Solaris is a bit strange, if there are no more entries in the
     * directory, it returns EINVAL.  Since this is against POSIX, we
     * hack around the problem here.  EINVAL is possible from other
     * readdir implementations, but only if the result buffer is too small.
     * since we control the size of that buffer, we should never have
     * that problem.
     */
    if (ret == EINVAL) {
        ret = APR_ENOENT;
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
#ifdef APR_USE_READDIR64_R
        /* If readdir64_r is used, check for the overflow case of trying
         * to fit a 64-bit integer into a 32-bit integer. */
        if (sizeof(apr_ino_t) >= sizeof(retent->DIRENT_INODE)
            || (apr_ino_t)retent->DIRENT_INODE == retent->DIRENT_INODE) {
            wanted &= ~APR_FINFO_INODE;
        } else {
            /* Prevent the fallback code below from filling in the
             * inode if the stat call fails. */
            retent->DIRENT_INODE = 0;
        }
#else
        wanted &= ~APR_FINFO_INODE;
#endif /* APR_USE_READDIR64_R */
    }
#endif /* DIRENT_INODE */

    wanted &= ~APR_FINFO_NAME;

    if (wanted)
    {
        char fspec[APR_PATH_MAX];
        char *end;

        end = apr_cpystrn(fspec, thedir->dirname, sizeof fspec);

        if (end > fspec && end[-1] != '/' && (end < fspec + APR_PATH_MAX))
            *end++ = '/';

        apr_cpystrn(end, thedir->entry->d_name, 
                    sizeof fspec - (end - fspec));

        ret = apr_stat(finfo, fspec, APR_FINFO_LINK | wanted, thedir->pool);
        /* We passed a stack name that will disappear */
        finfo->fname = NULL;
    }

    if (wanted && (ret == APR_SUCCESS || ret == APR_INCOMPLETE)) {
        wanted &= ~finfo->valid;
    }
    else {
        /* We don't bail because we fail to stat, when we are only