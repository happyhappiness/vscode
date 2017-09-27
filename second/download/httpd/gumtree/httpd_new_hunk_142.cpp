    /* WooHoo, we have a file to put in the cache */
    new_file = apr_pcalloc(cmd->pool, sizeof(a_file));
    new_file->finfo = tmp.finfo;

#if APR_HAS_MMAP
    if (mmap) {
        /* MMAPFile directive. MMAP'ing the file
         * XXX: APR_HAS_LARGE_FILES issue; need to reject this request if
         * size is greater than MAX(apr_size_t) (perhaps greater than 1M?).
         */
        if ((rc = apr_mmap_create(&new_file->mm, fd, 0, 
                                  (apr_size_t)new_file->finfo.size,
                                  APR_MMAP_READ, cmd->pool)) != APR_SUCCESS) { 
            apr_file_close(fd);
            ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
                         "mod_file_cache: unable to mmap %s, skipping", filename);
            return;
        }
        apr_file_close(fd);
        new_file->is_mmapped = TRUE;
    }
#endif
#if APR_HAS_SENDFILE
    if (!mmap) {
        /* CacheFile directive. Caching the file handle */
