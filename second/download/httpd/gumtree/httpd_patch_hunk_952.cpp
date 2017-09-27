     return res_buf;
 }
 
 AP_DECLARE(int) ap_cfg_closefile(ap_configfile_t *cfp)
 {
 #ifdef DEBUG
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, 
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
         "Done with config file %s", cfp->name);
 #endif
     return (cfp->close == NULL) ? 0 : cfp->close(cfp->param);
 }
 
 static apr_status_t cfg_close(void *param)
