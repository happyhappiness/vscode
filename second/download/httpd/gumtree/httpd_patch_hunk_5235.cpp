     const char *vdir = apr_pstrcat(pool, rest, CACHE_HEADER_SUFFIX,
             CACHE_VDIR_SUFFIX, NULL);
     const char *dirname = NULL;
 
     rv = apr_dir_open(&dirp, base, pool);
     if (rv != APR_SUCCESS) {
-        char errmsg[120];
-        apr_file_printf(errfile, "Could not open directory %s: %s" APR_EOL_STR,
-                base, apr_strerror(rv, errmsg, sizeof errmsg));
+        apr_file_printf(errfile, "Could not open directory %s: %pm" APR_EOL_STR,
+                base, &rv);
         return rv;
     }
 
     rv = APR_ENOENT;
 
     while (apr_dir_read(&dirent, APR_FINFO_DIRENT | APR_FINFO_TYPE, dirp)
