         if(res != APR_SUCCESS && !APR_STATUS_IS_EEXIST(res)) {
             ap_log_error(APLOG_MARK, APLOG_ERR, res, ap_server_conf, APLOGNO(00142)
                          "gprof: error creating directory %s", dir);
         }
     }
     else {
-        use_dir = ap_server_root_relative(pconf, DEFAULT_REL_RUNTIMEDIR);
+        use_dir = ap_runtime_dir_relative(pconf, "");
     }
 
     chdir(use_dir);
 }
 #else
 #define chdir_for_gprof()
