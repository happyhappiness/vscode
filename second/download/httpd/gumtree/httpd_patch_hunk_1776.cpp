             /* We need to copy the output headers and treat them as input
              * headers as well.  BUT, we need to do this before we remove
              * TE, so that they are preserved accordingly for
              * ap_http_filter to know where to end.
              */
             rp->headers_in = apr_table_copy(r->pool, r->headers_out);
+            /*
+             * Restore Transfer-Encoding header from response if we saved
+             * one before and there is none left. We need it for the
+             * ap_http_filter. See above.
+             */
+            if (te && !apr_table_get(rp->headers_in, "Transfer-Encoding")) {
+                apr_table_add(rp->headers_in, "Transfer-Encoding", te);
+            }
 
             apr_table_unset(r->headers_out,"Transfer-Encoding");
 
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "proxy: start body send");
 
