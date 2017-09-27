         return return_code;
     }
 
     return OK;
 }
 
+/* If requested, create a fake basic authentication header for the benefit
+ * of a proxy or application running behind this server.
+ */
+static int authenticate_basic_fake(request_rec *r)
+{
+    const char *auth_line, *user, *pass, *err;
+    auth_basic_config_rec *conf = ap_get_module_config(r->per_dir_config,
+                                                       &auth_basic_module);
+
+    if (!conf->fakeuser) {
+        return DECLINED;
+    }
+
+    user = ap_expr_str_exec(r, conf->fakeuser, &err);
+    if (err) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02455)
+                      "AuthBasicFake: could not evaluate user expression for URI '%s': %s", r->uri, err);
+        return HTTP_INTERNAL_SERVER_ERROR;
+    }
+    if (!user || !*user) {
+        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02458)
+                      "AuthBasicFake: empty username expression for URI '%s', ignoring", r->uri);
+
+        apr_table_unset(r->headers_in, "Authorization");
+
+        return DECLINED;
+    }
+
+    pass = ap_expr_str_exec(r, conf->fakepass, &err);
+    if (err) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02456)
+                      "AuthBasicFake: could not evaluate password expression for URI '%s': %s", r->uri, err);
+        return HTTP_INTERNAL_SERVER_ERROR;
+    }
+    if (!pass || !*pass) {
+        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02459)
+                      "AuthBasicFake: empty password expression for URI '%s', ignoring", r->uri);
+
+        apr_table_unset(r->headers_in, "Authorization");
+
+        return DECLINED;
+    }
+
+    auth_line = apr_pstrcat(r->pool, "Basic ",
+                            ap_pbase64encode(r->pool,
+                                             apr_pstrcat(r->pool, user,
+                                                         ":", pass, NULL)),
+                            NULL);
+    apr_table_setn(r->headers_in, "Authorization", auth_line);
+
+    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02457)
+                  "AuthBasicFake: \"Authorization: %s\"",
+                  auth_line);
+
+    return OK;
+}
+
 static void register_hooks(apr_pool_t *p)
 {
     ap_hook_check_authn(authenticate_basic_user, NULL, NULL, APR_HOOK_MIDDLE,
                         AP_AUTH_INTERNAL_PER_CONF);
+    ap_hook_fixups(authenticate_basic_fake, NULL, NULL, APR_HOOK_LAST);
     ap_hook_note_auth_failure(hook_note_basic_auth_failure, NULL, NULL,
                               APR_HOOK_MIDDLE);
 }
 
 AP_DECLARE_MODULE(auth_basic) =
 {
     STANDARD20_MODULE_STUFF,
     create_auth_basic_dir_config,  /* dir config creater */
-    NULL,                          /* dir merger --- default is to override */
+    merge_auth_basic_dir_config,   /* dir merger --- default is to override */
     NULL,                          /* server config */
     NULL,                          /* merge server config */
     auth_basic_cmds,               /* command apr_table_t */
     register_hooks                 /* register hooks */
 };
