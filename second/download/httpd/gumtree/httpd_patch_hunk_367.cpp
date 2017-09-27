         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "cache: %s not cached. Reason: %s", url, reason);
         /* remove this object from the cache 
          * BillS Asks.. Why do we need to make this call to remove_url?
          * leave it in for now..
          */
-        cache_remove_url(r, cache->types, url);
+        cache_remove_url(r, url);
 
         /* remove this filter from the chain */
         ap_remove_output_filter(f);
 
         /* ship the data up the stack */
         return ap_pass_brigade(f->next, in);
