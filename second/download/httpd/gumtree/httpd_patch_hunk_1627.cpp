     if (script && r->prev && r->prev->prev)
         return DECLINED;
 
     /* Second, check for actions (which override the method scripts) */
     action = r->handler ? r->handler :
         ap_field_noparam(r->pool, r->content_type);
-    action = action ? action : ap_default_type(r);
 
-    if ((t = apr_table_get(conf->action_types, action))) {
+    if (action && (t = apr_table_get(conf->action_types, action))) {
         if (*t++ == '0' && r->finfo.filetype == 0) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "File does not exist: %s", r->filename);
             return HTTP_NOT_FOUND;
         }
 
