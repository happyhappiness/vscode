                 ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                              "proxy: server %s returned Transfer-Encoding"
                              " and Content-Length", backend->hostname);
                 backend->close += 1;
             }
 
+            /*
+             * Save a possible Transfer-Encoding header as we need it later for
+             * ap_http_filter to know where to end.
+             */
+            te = apr_table_get(r->headers_out, "Transfer-Encoding");
             /* strip connection listed hop-by-hop headers from response */
             backend->close += ap_proxy_liststr(apr_table_get(r->headers_out,
                                                              "Connection"),
                                               "close");
             ap_proxy_clear_connection(p, r->headers_out);
             if ((buf = apr_table_get(r->headers_out, "Content-Type"))) {
                 ap_set_content_type(r, apr_pstrdup(p, buf));
             }
-            ap_proxy_pre_http_request(origin,rp);
+            if (!ap_is_HTTP_INFO(r->status)) {
+                ap_proxy_pre_http_request(origin, rp);
+            }
 
             /* Clear hop-by-hop headers */
             for (i=0; hop_by_hop_hdrs[i]; ++i) {
                 apr_table_unset(r->headers_out, hop_by_hop_hdrs[i]);
             }
             /* Delete warnings with wrong date */
