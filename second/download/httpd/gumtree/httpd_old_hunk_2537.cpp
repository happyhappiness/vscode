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
