     util_ald_free(cache, node->username);
     util_ald_free(cache, node->dn);
     util_ald_free(cache, node->bindpw);
     util_ald_free(cache, node);
 }
 
+void util_ldap_search_node_display(request_rec *r, util_ald_cache_t *cache, void *n)
+{
+    util_search_node_t *node = (util_search_node_t *)n;
+    char date_str[APR_CTIME_LEN+1];
+    char *buf;
+
+    apr_ctime(date_str, node->lastbind);
+
+    buf = apr_psprintf(r->pool, 
+             "<tr valign='top'>"
+             "<td nowrap>%s</td>"
+             "<td nowrap>%s</td>"
+             "<td nowrap>%s</td>"
+             "<tr>",
+         node->username,
+         node->dn,
+         date_str);
+
+    ap_rputs(buf, r);
+}
+
 /* ------------------------------------------------------------------ */
 
 unsigned long util_ldap_compare_node_hash(void *n)
 {
     util_compare_node_t *node = (util_compare_node_t *)n;
     return util_ald_hash_string(3, node->dn, node->attrib, node->value);
