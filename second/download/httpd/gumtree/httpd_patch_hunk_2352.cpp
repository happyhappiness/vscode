     }
 
     /* recursion state: ok */
     return 0;
 }
 
-static const char *add_ct_output_filters(cmd_parms *cmd, void *conf_,
-                                         const char *arg, const char *arg2)
-{
-    core_dir_config *conf = conf_;
-    ap_filter_rec_t *old, *new = NULL;
-    const char *filter_name;
-
-    if (!conf->ct_output_filters) {
-        conf->ct_output_filters = apr_hash_make(cmd->pool);
-        old = NULL;
-    }
-    else {
-        old = (ap_filter_rec_t*) apr_hash_get(conf->ct_output_filters, arg2,
-                                              APR_HASH_KEY_STRING);
-        /* find last entry */
-        if (old) {
-            while (old->next) {
-                old = old->next;
-            }
-        }
-    }
-
-    while (*arg &&
-           (filter_name = ap_getword(cmd->pool, &arg, ';')) &&
-           strcmp(filter_name, "")) {
-        new = apr_pcalloc(cmd->pool, sizeof(ap_filter_rec_t));
-        new->name = filter_name;
-
-        /* We found something, so let's append it.  */
-        if (old) {
-            old->next = new;
-        }
-        else {
-            apr_hash_set(conf->ct_output_filters, arg2,
-                         APR_HASH_KEY_STRING, new);
-        }
-        old = new;
-    }
-
-    if (!new) {
-        return "invalid filter name";
-    }
-
-    return NULL;
-}
-/*
- * Insert filters requested by the AddOutputFilterByType
- * configuration directive. We cannot add filters based
- * on content-type until after the handler has started
- * to run. Only then do we reliably know the content-type.
- */
-void ap_add_output_filters_by_type(request_rec *r)
-{
-    core_dir_config *conf;
-    const char *ctype;
-
-    conf = (core_dir_config *)ap_get_module_config(r->per_dir_config,
-                                                   &core_module);
-
-    /* We can't do anything with no content-type or if we don't have a
-     * filter configured.
-     */
-    if (!r->content_type || !conf->ct_output_filters) {
-        return;
-    }
-
-    /* remove c-t decoration */
-    ctype = ap_field_noparam(r->pool, r->content_type);
-    if (ctype) {
-        ap_filter_rec_t *ct_filter;
-        ct_filter = apr_hash_get(conf->ct_output_filters, ctype,
-                                 APR_HASH_KEY_STRING);
-        while (ct_filter) {
-            ap_add_output_filter(ct_filter->name, NULL, r, r->connection);
-            ct_filter = ct_filter->next;
-        }
-    }
-
-    return;
-}
-
 static const char *set_trace_enable(cmd_parms *cmd, void *dummy,
                                     const char *arg1)
 {
     core_server_config *conf = ap_get_module_config(cmd->server->module_config,
                                                     &core_module);
 
