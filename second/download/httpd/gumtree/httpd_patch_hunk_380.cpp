     util_ald_destroy_cache(node->search_cache);
     util_ald_destroy_cache(node->compare_cache);
     util_ald_destroy_cache(node->dn_compare_cache);
     util_ald_free(cache, node);
 }
 
+void util_ldap_url_node_display(request_rec *r, util_ald_cache_t *cache, void *n)
+{
+    util_url_node_t *node = (util_url_node_t *)n;
+    char date_str[APR_CTIME_LEN+1];
+    char *buf;
+    const char *type_str;
+    util_ald_cache_t *cache_node;
+    int x;
+
+    for (x=0;x<3;x++) {
+        switch (x) {
+            case 0:
+                cache_node = node->search_cache;
+                type_str = "Searches";
+                break;
+            case 1:
+                cache_node = node->compare_cache;
+                type_str = "Compares";
+                break;
+            case 2:
+                cache_node = node->dn_compare_cache;
+                type_str = "DN Compares";
+                break;
+        }
+        
+        if (cache_node->marktime) {
+            apr_ctime(date_str, cache_node->marktime);
+        }
+        else 
+            date_str[0] = 0;
+
+        buf = apr_psprintf(r->pool, 
+                 "<tr valign='top'>"
+                 "<td nowrap>%s (%s)</td>"
+                 "<td nowrap>%ld</td>"
+                 "<td nowrap>%ld</td>"
+                 "<td nowrap>%ld</td>"
+                 "<td nowrap>%ld</td>"
+                 "<td nowrap>%s</td>"
+                 "<tr>",
+             node->url,
+             type_str,
+             cache_node->size,
+             cache_node->maxentries,
+             cache_node->numentries,
+             cache_node->fullmark,
+             date_str);
+    
+        ap_rputs(buf, r);
+    }
+
+}
+
 /* ------------------------------------------------------------------ */
 
 /* Cache functions for search nodes */
 unsigned long util_ldap_search_node_hash(void *n)
 {
     util_search_node_t *node = (util_search_node_t *)n;
