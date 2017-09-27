 
 
 /*
  * Authorization header verification code
  */
 
-static const char *get_hash(request_rec *r, const char *user,
-                            const char *realm, const char *auth_pwfile)
+static authn_status get_hash(request_rec *r, const char *user,
+                             digest_config_rec *conf)
 {
-    ap_configfile_t *f;
-    char l[MAX_STRING_LEN];
-    const char *rpw;
-    char *w, *x;
-    apr_status_t sts;
+    authn_status auth_result;
+    char *password;
+    authn_provider_list *current_provider;
+
+    current_provider = conf->providers;
+    do {
+        const authn_provider *provider;
 
-    if ((sts = ap_pcfg_openfile(&f, r->pool, auth_pwfile)) != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, sts, r,
-                      "Digest: Could not open password file: %s", auth_pwfile);
-        return NULL;
-    }
-    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
-        if ((l[0] == '#') || (!l[0])) {
-            continue;
+        /* For now, if a provider isn't set, we'll be nice and use the file
+         * provider.
+         */
+        if (!current_provider) {
+            provider = ap_lookup_provider(AUTHN_PROVIDER_GROUP,
+                                          AUTHN_DEFAULT_PROVIDER, "0");
+
+            if (!provider || !provider->get_realm_hash) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                              "No Authn provider configured");
+                auth_result = AUTH_GENERAL_ERROR;
+                break;
+            }
+            apr_table_setn(r->notes, AUTHN_PROVIDER_NAME_NOTE, AUTHN_DEFAULT_PROVIDER);
+        }
+        else {
+            provider = current_provider->provider;
+            apr_table_setn(r->notes, AUTHN_PROVIDER_NAME_NOTE, current_provider->provider_name);
+        }
+
+
+        /* We expect the password to be md5 hash of user:realm:password */
+        auth_result = provider->get_realm_hash(r, user, conf->realm,
+                                               &password);
+
+        apr_table_unset(r->notes, AUTHN_PROVIDER_NAME_NOTE);
+
+        /* Something occured.  Stop checking. */
+        if (auth_result != AUTH_USER_NOT_FOUND) {
+            break;
         }
-        rpw = l;
-        w = ap_getword(r->pool, &rpw, ':');
-        x = ap_getword(r->pool, &rpw, ':');
 
-        if (x && w && !strcmp(user, w) && !strcmp(realm, x)) {
-            ap_cfg_closefile(f);
-            return apr_pstrdup(r->pool, rpw);
+        /* If we're not really configured for providers, stop now. */
+        if (!conf->providers) {
+           break;
         }
+
+        current_provider = current_provider->next;
+    } while (current_provider);
+
+    if (auth_result == AUTH_USER_FOUND) {
+        conf->ha1 = password;
     }
-    ap_cfg_closefile(f);
-    return NULL;
+
+    return auth_result;
 }
 
 static int check_nc(const request_rec *r, const digest_header_rec *resp,
                     const digest_config_rec *conf)
 {
     unsigned long nc;
