     if (!fname) {
         ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                      MODNAME ": Invalid magic file path %s", conf->magicfile);
         return -1;
     }
     if ((result = apr_file_open(&f, fname, APR_READ | APR_BUFFERED,
-                                APR_OS_DEFAULT, p) != APR_SUCCESS)) {
+                                APR_OS_DEFAULT, p)) != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ERR, result, s,
                      MODNAME ": can't read magic file %s", fname);
         return -1;
     }
 
     /* set up the magic list (empty) */
