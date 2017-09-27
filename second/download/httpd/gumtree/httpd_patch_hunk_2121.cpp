                            NULL);
     }
 
     return NULL;
 }
 
-/* find_code_page() is a fixup hook that decides if translation should be
- * enabled; if so, it sets up request data for use by the filter registration
- * hook so that it knows what to do
+/* find_code_page() is a fixup hook that checks if the module is
+ * configured and the input or output potentially need to be translated.
+ * If so, context is initialized for the filters.
  */
 static int find_code_page(request_rec *r)
 {
     charset_dir_t *dc = ap_get_module_config(r->per_dir_config,
                                              &charset_lite_module);
     charset_req_t *reqinfo;
     charset_filter_ctx_t *input_ctx, *output_ctx;
     apr_status_t rv;
-    const char *mime_type;
 
     if (dc->debug >= DBGLVL_FLOW) {
         ap_log_rerror(APLOG_MARK,APLOG_DEBUG, 0, r,
                       "uri: %s file: %s method: %d "
                       "imt: %s flags: %s%s%s %s->%s",
-                      r->uri, r->filename, r->method_number,
+                      r->uri,
+                      r->filename ? r->filename : "(none)",
+                      r->method_number,
                       r->content_type ? r->content_type : "(unknown)",
                       r->main     ? "S" : "",    /* S if subrequest */
                       r->prev     ? "R" : "",    /* R if redirect */
                       r->proxyreq ? "P" : "",    /* P if proxy */
                       dc->charset_source, dc->charset_default);
     }
