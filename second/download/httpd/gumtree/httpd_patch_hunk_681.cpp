 #if APR_HAS_MMAP
     if (mmap) {
         /* MMAPFile directive. MMAP'ing the file
          * XXX: APR_HAS_LARGE_FILES issue; need to reject this request if
          * size is greater than MAX(apr_size_t) (perhaps greater than 1M?).
          */
-        if ((rc = apr_mmap_create(&new_file->mm, fd, 0, 
+        if ((rc = apr_mmap_create(&new_file->mm, fd, 0,
                                   (apr_size_t)new_file->finfo.size,
-                                  APR_MMAP_READ, cmd->pool)) != APR_SUCCESS) { 
+                                  APR_MMAP_READ, cmd->pool)) != APR_SUCCESS) {
             apr_file_close(fd);
             ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
                          "mod_file_cache: unable to mmap %s, skipping", filename);
             return;
         }
         apr_file_close(fd);
