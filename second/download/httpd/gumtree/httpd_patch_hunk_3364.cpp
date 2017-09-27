         use_dir = ap_server_root_relative(pconf, buf ? buf : dir);
         res = apr_dir_make(use_dir,
                            APR_UREAD | APR_UWRITE | APR_UEXECUTE |
                            APR_GREAD | APR_GEXECUTE |
                            APR_WREAD | APR_WEXECUTE, pconf);
         if(res != APR_SUCCESS && !APR_STATUS_IS_EEXIST(res)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, res, ap_server_conf,
+            ap_log_error(APLOG_MARK, APLOG_ERR, res, ap_server_conf, APLOGNO(00142)
                          "gprof: error creating directory %s", dir);
         }
     }
     else {
         use_dir = ap_server_root_relative(pconf, DEFAULT_REL_RUNTIMEDIR);
     }
