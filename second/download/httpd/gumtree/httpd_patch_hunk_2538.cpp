 static const char *cachefilehandle(cmd_parms *cmd, void *dummy, const char *filename)
 {
 #if APR_HAS_SENDFILE
     cache_the_file(cmd, filename, 0);
 #else
     /* Sendfile not supported by this OS */
-    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
-                 "mod_file_cache: unable to cache file: %s. Sendfile is not supported on this OS", filename);
+    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00800)
+                 "unable to cache file: %s. Sendfile is not supported on this OS", filename);
 #endif
     return NULL;
 }
 static const char *cachefilemmap(cmd_parms *cmd, void *dummy, const char *filename)
 {
 #if APR_HAS_MMAP
     cache_the_file(cmd, filename, 1);
 #else
     /* MMAP not supported by this OS */
-    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
-                 "mod_file_cache: unable to cache file: %s. MMAP is not supported by this OS", filename);
+    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00801)
+                 "unable to cache file: %s. MMAP is not supported by this OS", filename);
 #endif
     return NULL;
 }
 
 static int file_cache_post_config(apr_pool_t *p, apr_pool_t *plog,
                                    apr_pool_t *ptemp, server_rec *s)
