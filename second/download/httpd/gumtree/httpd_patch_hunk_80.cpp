         rv = cache_create_entity(r, cache->types, url, size);
     }
     
     if (rv != OK) {
         /* Caching layer declined the opportunity to cache the response */
         ap_remove_output_filter(f);
-        if (split_point) {
-            apr_bucket_brigade *already_sent = in;
-            in = apr_brigade_split(in, split_point);
-            apr_brigade_destroy(already_sent);
-        }
         return ap_pass_brigade(f->next, in);
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                  "cache: Caching url: %s", url);
 
