     const char *errmsg;
 
     if ((rv == APR_SUCCESS) || (rv == APR_ENOTIMPL)) {
         return APR_SUCCESS;
     }
 
-    errmsg = apr_dbd_error(rec->driver, rec->handle, rv);
+    /* we don't have a driver-specific error code, so we'll just pass
+     * a "success" value and rely on the driver to ignore it
+     */
+    errmsg = apr_dbd_error(rec->driver, rec->handle, 0);
     if (!errmsg) {
         errmsg = "(unknown)";
     }
 
     svr = ap_get_module_config(s->module_config, &dbd_module);
     ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
