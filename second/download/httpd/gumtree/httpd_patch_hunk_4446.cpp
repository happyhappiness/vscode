          *  Apply the current rule.
          */
         ctx->vary = NULL;
         rc = apply_rewrite_rule(p, ctx);
 
         if (rc) {
+
+            /* Catch looping rules with pathinfo growing unbounded */
+            if ( strlen( r->filename ) > 2*r->server->limit_req_line ) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                              "RewriteRule '%s' and URI '%s' "
+                              "exceeded maximum length (%d)", 
+                              p->pattern, r->uri, 2*r->server->limit_req_line );
+                r->status = HTTP_INTERNAL_SERVER_ERROR;
+                return ACTION_STATUS;
+            }
+
             /* Regardless of what we do next, we've found a match. Check to see
              * if any of the request header fields were involved, and add them
              * to the Vary field of the response.
              */
             if (ctx->vary) {
                 apr_table_merge(r->headers_out, "Vary", ctx->vary);
