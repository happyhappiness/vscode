             memcpy((char *) finfo, (const char *) &rr->finfo,
                    sizeof(rr->finfo));
             ap_destroy_sub_req(rr);
             return 0;
         }
         else {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unable to get "
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01339) "unable to get "
                           "information about \"%s\" in parsed file %s",
                           tag_val, r->filename);
             ap_destroy_sub_req(rr);
             return -1;
         }
     }
     else {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter \"%s\" "
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01340) "unknown parameter \"%s\" "
                       "to tag %s in %s", tag, directive, r->filename);
         return -1;
     }
 }
 
 /*
- * <!--#include virtual|file="..." [virtual|file="..."] ... -->
+ * <!--#include virtual|file="..." [onerror|virtual|file="..."] ... -->
+ *
+ * Output each file/virtual in turn until one of them returns an error.
+ * On error, ignore all further file/virtual attributes until we reach
+ * an onerror attribute, where we make an attempt to serve the onerror
+ * virtual url. If onerror fails, or no onerror is present, the default
+ * error string is inserted into the stream.
  */
 static apr_status_t handle_include(include_ctx_t *ctx, ap_filter_t *f,
                                    apr_bucket_brigade *bb)
 {
     request_rec *r = f->r;
+    char *last_error;
 
     if (!ctx->argc) {
         ap_log_rerror(APLOG_MARK,
                       (ctx->flags & SSI_FLAG_PRINTING)
                           ? APLOG_ERR : APLOG_WARNING,
-                      0, r, "missing argument for include element in %s",
+                      0, r, APLOGNO(01341)
+                      "missing argument for include element in %s",
                       r->filename);
     }
 
     if (!(ctx->flags & SSI_FLAG_PRINTING)) {
         return APR_SUCCESS;
     }
 
     if (!ctx->argc) {
         SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
         return APR_SUCCESS;
     }
 
+    last_error = NULL;
     while (1) {
         char *tag     = NULL;
         char *tag_val = NULL;
         request_rec *rr = NULL;
         char *error_fmt = NULL;
         char *parsed_string;
 
         ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
         if (!tag || !tag_val) {
             break;
         }
 
-        if (strcmp(tag, "virtual") && strcmp(tag, "file")) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
+        if (strcmp(tag, "virtual") && strcmp(tag, "file") && strcmp(tag,
+                "onerror")) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01342) "unknown parameter "
                           "\"%s\" to tag include in %s", tag, r->filename);
             SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
             break;
         }
 
         parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
