             if (ap_cache_request_is_conditional(r)) {
                 ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                              r->server,
                              "cache: conditional - add cache_in filter and "
                              "DECLINE");
                 /* Why not add CACHE_CONDITIONAL? */
-                ap_add_output_filter("CACHE_IN", NULL, r, r->connection);
+                ap_add_output_filter_handle(cache_in_filter_handle, NULL,
+                                            r, r->connection);
 
                 return DECLINED;
             }
             /* else if non-conditional request */
             else {
                 /* fudge response into a conditional */
