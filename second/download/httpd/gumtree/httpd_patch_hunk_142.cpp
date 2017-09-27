     /* WooHoo, we have a file to put in the cache */
     new_file = apr_pcalloc(cmd->pool, sizeof(a_file));
     new_file->finfo = tmp.finfo;
 
 #if APR_HAS_MMAP
     if (mmap) {
-        apr_mmap_t *mm;
-
         /* MMAPFile directive. MMAP'ing the file
          * XXX: APR_HAS_LARGE_FILES issue; need to reject this request if
          * size is greater than MAX(apr_size_t) (perhaps greater than 1M?).
          */
-        if ((rc = apr_mmap_create(&mm, fd, 0, 
+        if ((rc = apr_mmap_create(&new_file->mm, fd, 0, 
                                   (apr_size_t)new_file->finfo.size,
                                   APR_MMAP_READ, cmd->pool)) != APR_SUCCESS) { 
             apr_file_close(fd);
             ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
                          "mod_file_cache: unable to mmap %s, skipping", filename);
             return;
         }
         apr_file_close(fd);
-        /* We want to cache an apr_mmap_t that's marked as "non-owner"
-         * to pass to each request so that mmap_setaside()'s call to
-         * apr_mmap_dup() will never try to move the apr_mmap_t to a
-         * different pool.  This apr_mmap_t is already going to live
-         * longer than any request, but mmap_setaside() has no way to
-         * know that because it's allocated out of cmd->pool,
-         * which is disjoint from r->pool.
-         */
-        apr_mmap_dup(&new_file->mm, mm, cmd->pool, 0);
         new_file->is_mmapped = TRUE;
     }
 #endif
 #if APR_HAS_SENDFILE
     if (!mmap) {
         /* CacheFile directive. Caching the file handle */
