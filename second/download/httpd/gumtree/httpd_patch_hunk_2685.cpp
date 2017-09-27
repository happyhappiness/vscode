 #endif
 
     /** IG: Now that we've merged to the final config, go one last time
      *  through the chain, and prune out the NULL filters */
 
     for (p = cfg->chain; p; p = p->next) {
-        if (p->fname == NULL) 
+        if (p->fname == NULL)
             cfg->chain = p->next;
     }
 
     for (p = cfg->chain; p; p = p->next) {
         filter = apr_hash_get(cfg->live_filters, p->fname, APR_HASH_KEY_STRING);
         if (filter == NULL) {
-            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01380)
                           "Unknown filter %s not added", p->fname);
             continue;
         }
         ap_add_output_filter_handle(filter, NULL, r, r->connection);
 #ifndef NO_PROTOCOL
         if (ranges && (filter->proto_flags
