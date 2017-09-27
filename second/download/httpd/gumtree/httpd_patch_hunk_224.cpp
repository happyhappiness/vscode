         new->active = base->active;
     }
     else {
         new->active = add->active;
     }
 
-    if (add->expiresdefault[0] != '\0') {
+    if (add->expiresdefault != NULL) {
         new->expiresdefault = add->expiresdefault;
     }
     else {
 	new->expiresdefault = base->expiresdefault;
     }
-
+    new->wildcards = add->wildcards;
     new->expiresbytype = apr_table_overlay(p, add->expiresbytype,
                                         base->expiresbytype);
     return new;
 }
 
-static int add_expires(request_rec *r)
+/*
+ * Handle the setting of the expiration response header fields according
+ * to our criteria.
+ */
+
+static int set_expiration_fields(request_rec *r, const char *code,
+                                 apr_table_t *t)
 {
-    expires_dir_config *conf;
-    char *code;
     apr_time_t base;
     apr_time_t additional;
     apr_time_t expires;
     int additional_sec;
     char *timestr;
 
-    if (ap_is_HTTP_ERROR(r->status))       /* Don't add Expires headers to errors */
-        return DECLINED;
-
-    if (r->main != NULL)        /* Say no to subrequests */
-        return DECLINED;
-
-    conf = (expires_dir_config *) ap_get_module_config(r->per_dir_config, &expires_module);
-    if (conf == NULL) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                    "internal error: %s", r->filename);
-        return HTTP_INTERNAL_SERVER_ERROR;
-    }
-
-    if (conf->active != ACTIVE_ON)
-        return DECLINED;
-
-    /* we perhaps could use the default_type(r) in its place but that
-     * may be 2nd guesing the desired configuration...  calling table_get
-     * with a NULL key will SEGV us
-     *
-     * I still don't know *why* r->content_type would ever be NULL, this
-     * is possibly a result of fixups being called in many different
-     * places.  Fixups is probably the wrong place to be doing all this
-     * work...  Bah.
-     *
-     * Changed as of 08.Jun.96 don't DECLINE, look for an ExpiresDefault.
-     */
-    if (r->content_type == NULL)
-        code = NULL;
-    else
-        code = (char *) apr_table_get(conf->expiresbytype, 
-		ap_field_noparam(r->pool, r->content_type));
-
-    if (code == NULL) {
-        /* no expires defined for that type, is there a default? */
-        code = conf->expiresdefault;
-
-        if (code[0] == '\0')
-            return OK;
-    }
-
-    /* we have our code */
-
     switch (code[0]) {
     case 'M':
 	if (r->finfo.filetype == 0) { 
 	    /* file doesn't exist on disk, so we can't do anything based on
 	     * modification time.  Note that this does _not_ log an error.
 	     */
