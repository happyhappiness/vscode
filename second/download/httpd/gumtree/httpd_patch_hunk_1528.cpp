             /* Treat as stale, causing revalidation */
             return 0;
         }
 
         ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                      "Incoming request is asking for a uncached version of "
-                     "%s, but we have been configured to ignore it and "
-                     "serve a cached response anyway",
+                     "%s, but we know better and are ignoring it",
                      r->unparsed_uri);
     }
 
     /* These come from the cached entity. */
     cc_cresp = apr_table_get(h->resp_hdrs, "Cache-Control");
     expstr = apr_table_get(h->resp_hdrs, "Expires");
