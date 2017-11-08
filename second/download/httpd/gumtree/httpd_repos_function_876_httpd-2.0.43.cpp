static void cache_the_file(cmd_parms *cmd, const char *filename, int mmap)
{
    a_server_config *sconf;
    a_file *new_file;
    a_file tmp;
    apr_file_t *fd = NULL;
    apr_status_t rc;
    const char *fspec;

    fspec = ap_server_root_relative(cmd->pool, filename);
    if (!fspec) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, APR_EBADPATH, cmd->server,
                     "mod_file_cache: invalid file path "
                     "%s, skipping", filename);
	return;
    }
    if ((rc = apr_stat(&tmp.finfo, fspec, APR_FINFO_MIN, 
                                 cmd->temp_pool)) != APR_SUCCESS) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
	    "mod_file_cache: unable to stat(%s), skipping", fspec);
	return;
    }
    if (tmp.finfo.filetype != APR_REG) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
	    "mod_file_cache: %s isn't a regular file, skipping", fspec);
	return;
    }
    if (tmp.finfo.size > AP_MAX_SENDFILE) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
	    "mod_file_cache: %s is too large to cache, skipping", fspec);
	return;
    }

    rc = apr_file_open(&fd, fspec, APR_READ | APR_BINARY | APR_XTHREAD,
                       APR_OS_DEFAULT, cmd->pool);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
                     "mod_file_cache: unable to open(%s, O_RDONLY), skipping", fspec);
	return;
    }
    apr_file_inherit_set(fd);

    /* WooHoo, we have a file to put in the cache */
    new_file = apr_pcalloc(cmd->pool, sizeof(a_file));
    new_file->finfo = tmp.finfo;

#if APR_HAS_MMAP
    if (mmap) {
        apr_mmap_t *mm;

        /* MMAPFile directive. MMAP'ing the file
         * XXX: APR_HAS_LARGE_FILES issue; need to reject this request if
         * size is greater than MAX(apr_size_t) (perhaps greater than 1M?).
         */
        if ((rc = apr_mmap_create(&mm, fd, 0, 
                                  (apr_size_t)new_file->finfo.size,
                                  APR_MMAP_READ, cmd->pool)) != APR_SUCCESS) { 
            apr_file_close(fd);
            ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
                         "mod_file_cache: unable to mmap %s, skipping", filename);
            return;
        }
        apr_file_close(fd);
        /* We want to cache an apr_mmap_t that's marked as "non-owner"
         * to pass to each request so that mmap_setaside()'s call to
         * apr_mmap_dup() will never try to move the apr_mmap_t to a
         * different pool.  This apr_mmap_t is already going to live
         * longer than any request, but mmap_setaside() has no way to
         * know that because it's allocated out of cmd->pool,
         * which is disjoint from r->pool.
         */
        apr_mmap_dup(&new_file->mm, mm, cmd->pool, 0);
        new_file->is_mmapped = TRUE;
    }
#endif
#if APR_HAS_SENDFILE
    if (!mmap) {
        /* CacheFile directive. Caching the file handle */
        new_file->is_mmapped = FALSE;
        new_file->file = fd;
    }
#endif

    new_file->filename = fspec;
    apr_rfc822_date(new_file->mtimestr, new_file->finfo.mtime);
    apr_snprintf(new_file->sizestr, sizeof new_file->sizestr, "%" APR_OFF_T_FMT, new_file->finfo.size);

    sconf = ap_get_module_config(cmd->server->module_config, &file_cache_module);
    apr_hash_set(sconf->fileht, new_file->filename, strlen(new_file->filename), new_file);

    if (apr_hash_count(sconf->fileht) == 1) {
	/* first one, register the cleanup */
	apr_pool_cleanup_register(cmd->pool, sconf, cleanup_file_cache, apr_pool_cleanup_null);
    }
}