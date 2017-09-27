         state != rsl_encoding) {
         /* defer to other modules */
         return DECLINED;
     }
 
     /* save the info in the request record */
-    if (state == rsl_subtype || state == rsl_encoding ||
-        state == rsl_encoding) {
-        char *tmp;
-        tmp = rsl_strdup(r, type_frag, type_pos, type_len);
-        /* XXX: this could be done at config time I'm sure... but I'm
-         * confused by all this magic_rsl stuff. -djg */
-        ap_content_type_tolower(tmp);
-        ap_set_content_type(r, tmp);
-    }
+    tmp = rsl_strdup(r, type_frag, type_pos, type_len);
+    /* XXX: this could be done at config time I'm sure... but I'm
+     * confused by all this magic_rsl stuff. -djg */
+    ap_content_type_tolower(tmp);
+    ap_set_content_type(r, tmp);
+
     if (state == rsl_encoding) {
-        char *tmp;
         tmp = rsl_strdup(r, encoding_frag,
                                          encoding_pos, encoding_len);
         /* XXX: this could be done at config time I'm sure... but I'm
          * confused by all this magic_rsl stuff. -djg */
         ap_str_tolower(tmp);
         r->content_encoding = tmp;
     }
 
     /* detect memory allocation or other errors */
     if (!r->content_type ||
         (state == rsl_encoding && !r->content_encoding)) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01511)
                       MODNAME ": unexpected state %d; could be caused by bad "
                       "data in magic file",
                       state);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
