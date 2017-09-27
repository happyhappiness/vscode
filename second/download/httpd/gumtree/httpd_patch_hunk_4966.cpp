 
 static void child_errfn(apr_pool_t *pool, apr_status_t err, const char *description)
 {
     request_rec *r;
     void *vr;
     apr_file_t *stderr_log;
-    char errbuf[200];
     char time_str[APR_CTIME_LEN];
 
     apr_pool_userdata_get(&vr, ERRFN_USERDATA_KEY, pool);
     r = vr;
     apr_file_open_stderr(&stderr_log, pool);
     ap_recent_ctime(time_str, apr_time_now());
     apr_file_printf(stderr_log,
-                    "[%s] [client %s] mod_ext_filter (%d)%s: %s\n",
+                    "[%s] [client %s] mod_ext_filter (%d)%pm: %s\n",
                     time_str,
                     r->useragent_ip,
                     err,
-                    apr_strerror(err, errbuf, sizeof(errbuf)),
+                    &err,
                     description);
 }
 
 /* init_ext_filter_process: get the external filter process going
  * This is per-filter-instance (i.e., per-request) initialization.
  */
