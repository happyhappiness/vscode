     util_url_node_t *n = NULL;
 
     util_ald_cache_t *util_ldap_cache = st->util_ldap_cache;
 
 
     if (!util_ldap_cache) {
-        return "<tr valign='top'><td nowrap colspan=7>Cache has not been enabled/initialised.</td></tr>";
+        ap_rputs("<tr valign='top'><td nowrap colspan=7>Cache has not been enabled/initialised.</td></tr>", r);
+        return NULL;
     }
 
     if (r->args && strlen(r->args)) {
         char cachetype[5], lint[2];
         unsigned int id, off;
         char date_str[APR_CTIME_LEN+1];
