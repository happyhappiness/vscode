                            | APR_READ | APR_BINARY | APR_XTHREAD | APR_FILE_NOCLEANUP);
             rv = apr_file_open(&tmpfile, name, mobj->flags,
                                APR_OS_DEFAULT, r->pool);
             if (rv != APR_SUCCESS) {
                 return rv;
             }
-            apr_file_unset_inherit(tmpfile);
+            apr_file_inherit_unset(tmpfile);
             apr_os_file_get(&(mobj->fd), tmpfile);
 
             /* Open for business */
             ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                          "mem_cache: Cached file: %s with key: %s", name, obj->key);
             obj->complete = 1;
