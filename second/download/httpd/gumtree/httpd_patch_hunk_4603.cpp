 
     /* Second, check for actions (which override the method scripts) */
     action = r->handler ? r->handler :
         ap_field_noparam(r->pool, r->content_type);
 
     if (action && (t = apr_table_get(conf->action_types, action))) {
-        if (*t++ == '0' && r->finfo.filetype == APR_NOFILE) {
+        int virtual = (*t++ == '0' ? 0 : 1);
+        if (!virtual && r->finfo.filetype == APR_NOFILE) {
             ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00652)
                           "File does not exist: %s", r->filename);
             return HTTP_NOT_FOUND;
         }
 
         script = t;
         /* propagate the handler name to the script
          * (will be REDIRECT_HANDLER there)
          */
         apr_table_setn(r->subprocess_env, "HANDLER", action);
+        if (virtual) {
+            apr_table_setn(r->notes, "virtual_script", "1");
+        }
     }
 
     if (script == NULL)
         return DECLINED;
 
     ap_internal_redirect_handler(apr_pstrcat(r->pool, script,
