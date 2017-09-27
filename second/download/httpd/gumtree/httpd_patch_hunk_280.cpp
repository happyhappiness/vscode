     st->cert_file_type = LDAP_CA_TYPE_UNKNOWN;
     st->ssl_support = 0;
 
     return st;
 }
 
-static void util_ldap_init_module(apr_pool_t *pool, server_rec *s)
-{
-    util_ldap_state_t *st = 
-        (util_ldap_state_t *)ap_get_module_config(s->module_config, 
-						  &ldap_module);
-
-    apr_status_t result = util_ldap_cache_init(pool, st->cache_bytes);
-    char buf[MAX_STRING_LEN];
-
-    apr_strerror(result, buf, sizeof(buf));
-    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, result, s, 
-                      "[%d] ldap cache init: %s", 
-                      getpid(), buf);
-}
-
-
 static apr_status_t util_ldap_cleanup_module(void *data)
 {
     server_rec *s = data;
 
     util_ldap_state_t *st = (util_ldap_state_t *)ap_get_module_config(
                                           s->module_config, &ldap_module);
