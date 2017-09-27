         ap_unescape_url(arg_copy);
         apr_table_setn(e, "QUERY_STRING_UNESCAPED",
                        ap_escape_shell_cmd(r->pool, arg_copy));
     }
 }
 
+static void cgi_child_errfn(apr_pool_t *pool, apr_status_t err,
+                            const char *description)
+{
+    apr_file_t *stderr_log;
+    char errbuf[200];
+
+    apr_file_open_stderr(&stderr_log, pool);
+    apr_file_printf(stderr_log,
+                    "(%d)%s: %s\n",
+                    err,
+                    apr_strerror(err, errbuf, sizeof(errbuf)),
+                    description);
+}
+
 static apr_status_t run_cgi_child(apr_file_t **script_out,
                                   apr_file_t **script_in,
                                   apr_file_t **script_err, 
                                   const char *command,
                                   const char * const argv[],
                                   request_rec *r,
