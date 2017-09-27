     }
     else {
         return 0;
     }
 }
 
-static authz_status env_check_authorization(request_rec *r, const char *require_line)
+static const char *ip_parse_config(cmd_parms *cmd,
+                                   const char *require_line,
+                                   const void **parsed_require_line)
 {
     const char *t, *w;
+    int count = 0;
+    apr_ipsubnet_t **ip;
+    apr_pool_t *ptemp = cmd->temp_pool;
+    apr_pool_t *p = cmd->pool;
 
-    /* The 'env' provider will allow the configuration to specify a list of
-        env variables to check rather than a single variable.  This is different
+    /* The 'ip' provider will allow the configuration to specify a list of
+        ip addresses to check rather than a single address.  This is different
         from the previous host based syntax. */
+
     t = require_line;
-    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
-        if (apr_table_get(r->subprocess_env, w)) {
-            return AUTHZ_GRANTED;
-        }
-    }
+    while ((w = ap_getword_conf(ptemp, &t)) && w[0])
+        count++;
 
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                  "access to %s failed, reason: env variable list does not meet "
-                  "'require'ments for user '%s' to be allowed access",
-                  r->uri, r->user);
+    if (count == 0)
+        return "'require ip' requires an argument";
 
-    return AUTHZ_DENIED;
-}
-
-static authz_status ip_check_authorization(request_rec *r, const char *require_line)
-{
-    const char *t, *w;
+    ip = apr_pcalloc(p, sizeof(apr_ipsubnet_t *) * (count + 1));
+    *parsed_require_line = ip;
 
-    /* The 'ip' provider will allow the configuration to specify a list of
-        ip addresses to check rather than a single address.  This is different
-        from the previous host based syntax. */
     t = require_line;
-    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
-        char *where = apr_pstrdup(r->pool, w);
-        char *s;
-        char msgbuf[120];
-        apr_ipsubnet_t *ip;
+    while ((w = ap_getword_conf(ptemp, &t)) && w[0]) {
+        char *addr = apr_pstrdup(ptemp, w);
+        char *mask;
         apr_status_t rv;
-        int got_ip = 0;
 
-        if ((s = ap_strchr(where, '/'))) {
-            *s++ = '\0';
-            rv = apr_ipsubnet_create(&ip, where, s, r->pool);
-            if(APR_STATUS_IS_EINVAL(rv)) {
-                /* looked nothing like an IP address */
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                              "an ip address 'require' list appears to be invalid ");
-            }
-            else if (rv != APR_SUCCESS) {
-                apr_strerror(rv, msgbuf, sizeof msgbuf);
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                              "an ip address 'require' list appears to be invalid; %s ",
-                              msgbuf);
-            }
-            else
-                got_ip = 1;
-        }
-        else if (!APR_STATUS_IS_EINVAL(rv = apr_ipsubnet_create(&ip, where,
-                                                                NULL, r->pool))) {
-            if (rv != APR_SUCCESS) {
-                apr_strerror(rv, msgbuf, sizeof msgbuf);
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                              "an ip address 'require' list appears to be invalid; %s ",
-                              msgbuf);
-            }
-            else 
-                got_ip = 1;
+        if (parsed_subnets &&
+            (*ip = apr_hash_get(parsed_subnets, w, APR_HASH_KEY_STRING)) != NULL)
+        {
+            /* we already have parsed this subnet */
+            ip++;
+            continue;
         }
 
-        if (got_ip && apr_ipsubnet_test(ip, r->connection->remote_addr)) {
-            return AUTHZ_GRANTED;
+        if ((mask = ap_strchr(addr, '/')))
+            *mask++ = '\0';
+
+        rv = apr_ipsubnet_create(ip, addr, mask, p);
+
+        if(APR_STATUS_IS_EINVAL(rv)) {
+            /* looked nothing like an IP address */
+            return apr_psprintf(p, "ip address '%s' appears to be invalid", w);
+        }
+        else if (rv != APR_SUCCESS) {
+            char msgbuf[120];
+            apr_strerror(rv, msgbuf, sizeof msgbuf);
+            return apr_psprintf(p, "ip address '%s' appears to be invalid: %s",
+                                w, msgbuf);
         }
+
+        if (parsed_subnets)
+            apr_hash_set(parsed_subnets, w, APR_HASH_KEY_STRING, *ip);
+        ip++;
     }
 
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                  "access to %s failed, reason: ip address list does not meet "
-                  "'require'ments for user '%s' to be allowed access",
-                  r->uri, r->user);
+    return NULL;
+}
+
+static authz_status ip_check_authorization(request_rec *r,
+                                           const char *require_line,
+                                           const void *parsed_require_line)
+{
+    /* apr_ipsubnet_test should accept const but doesn't */
+    apr_ipsubnet_t **ip = (apr_ipsubnet_t **)parsed_require_line;
+
+    while (*ip) {
+        if (apr_ipsubnet_test(*ip, r->useragent_addr))
+            return AUTHZ_GRANTED;
+        ip++;
+    }
 
+    /* authz_core will log the require line and the result at DEBUG */
     return AUTHZ_DENIED;
 }
 
-static authz_status host_check_authorization(request_rec *r, const char *require_line)
+static authz_status host_check_authorization(request_rec *r,
+                                             const char *require_line,
+                                             const void *parsed_require_line)
 {
     const char *t, *w;
     const char *remotehost = NULL;
     int remotehost_is_ip;
 
     remotehost = ap_get_remote_host(r->connection,
                                     r->per_dir_config,
                                     REMOTE_DOUBLE_REV,
                                     &remotehost_is_ip);
 
     if ((remotehost == NULL) || remotehost_is_ip) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                      "access to %s failed, reason: unable to get the "
-                      "remote host name", r->uri);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01753)
+                      "access check of '%s' to %s failed, reason: unable to get the "
+                      "remote host name", require_line, r->uri);
     }
     else {
         /* The 'host' provider will allow the configuration to specify a list of
             host names to check rather than a single name.  This is different
             from the previous host based syntax. */
         t = require_line;
         while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
             if (in_domain(w, remotehost)) {
                 return AUTHZ_GRANTED;
             }
         }
-
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                      "access to %s failed, reason: host name list does not meet "
-                      "'require'ments for user '%s' to be allowed access",
-                      r->uri, r->user);
     }
 
+    /* authz_core will log the require line and the result at DEBUG */
     return AUTHZ_DENIED;
 }
 
-static authz_status all_check_authorization(request_rec *r, const char *require_line)
-{
-    /* If the argument to the 'all' provider is 'granted' then just let 
-        everybody in. This would be equivalent to the previous syntax of
-        'allow from all'. If the argument is anything else, this would
-        be equivalent to 'deny from all' Of course the opposite would be 
-        true if the 'all' provider is invoked by the 'reject' directive */
-    if (strcasecmp(require_line, "granted") == 0) {
+static authz_status local_check_authorization(request_rec *r,
+                                              const char *require_line,
+                                              const void *parsed_require_line)
+{
+     if (   apr_sockaddr_equal(r->connection->local_addr,
+                               r->useragent_addr)
+         || apr_ipsubnet_test(localhost_v4, r->useragent_addr)
+#if APR_HAVE_IPV6
+         || apr_ipsubnet_test(localhost_v6, r->useragent_addr)
+#endif
+        )
+     {
         return AUTHZ_GRANTED;
-    }
-    return AUTHZ_DENIED;
-}
+     }
 
-static const authz_provider authz_env_provider =
-{
-    &env_check_authorization,
-};
+     return AUTHZ_DENIED;
+}
 
 static const authz_provider authz_ip_provider =
 {
     &ip_check_authorization,
+    &ip_parse_config,
 };
 
 static const authz_provider authz_host_provider =
 {
     &host_check_authorization,
+    NULL,
 };
 
-static const authz_provider authz_all_provider =
+static const authz_provider authz_local_provider =
 {
-    &all_check_authorization,
+    &local_check_authorization,
+    NULL,
 };
 
+
+static int authz_host_pre_config(apr_pool_t *p, apr_pool_t *plog,
+                                 apr_pool_t *ptemp)
+{
+    /* we only use this hash in the parse config phase, ptemp is enough */
+    parsed_subnets = apr_hash_make(ptemp);
+
+    apr_ipsubnet_create(&localhost_v4, "127.0.0.0", "8", p);
+    apr_hash_set(parsed_subnets, "127.0.0.0/8", APR_HASH_KEY_STRING, localhost_v4);
+
+#if APR_HAVE_IPV6
+    apr_ipsubnet_create(&localhost_v6, "::1", NULL, p);
+    apr_hash_set(parsed_subnets, "::1", APR_HASH_KEY_STRING, localhost_v6);
+#endif
+
+    return OK;
+}
+
+static int authz_host_post_config(apr_pool_t *p, apr_pool_t *plog,
+                                  apr_pool_t *ptemp, server_rec *s)
+{
+    /* make sure we don't use this during .htaccess parsing */
+    parsed_subnets = NULL;
+
+    return OK;
+}
+
 static void register_hooks(apr_pool_t *p)
 {
-    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "env",
-                              AUTHZ_PROVIDER_VERSION,
-                              &authz_env_provider, AP_AUTH_INTERNAL_PER_CONF);
+    ap_hook_pre_config(authz_host_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_post_config(authz_host_post_config, NULL, NULL, APR_HOOK_MIDDLE);
+
     ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ip",
                               AUTHZ_PROVIDER_VERSION,
                               &authz_ip_provider, AP_AUTH_INTERNAL_PER_CONF);
     ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "host",
                               AUTHZ_PROVIDER_VERSION,
                               &authz_host_provider, AP_AUTH_INTERNAL_PER_CONF);
-    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "all",
+    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "local",
                               AUTHZ_PROVIDER_VERSION,
-                              &authz_all_provider, AP_AUTH_INTERNAL_PER_CONF);
+                              &authz_local_provider, AP_AUTH_INTERNAL_PER_CONF);
 }
 
 AP_DECLARE_MODULE(authz_host) =
 {
     STANDARD20_MODULE_STUFF,
-    create_authz_host_dir_config,   /* dir config creater */
+    NULL,                           /* dir config creater */
     NULL,                           /* dir merger --- default is to override */
     NULL,                           /* server config */
     NULL,                           /* merge server config */
-    authz_host_cmds,
+    NULL,
     register_hooks                  /* register hooks */
 };
