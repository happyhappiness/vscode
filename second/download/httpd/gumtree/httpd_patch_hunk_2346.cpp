                 ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                               "proxy: *: found forward proxy worker for %s",
                               *url);
                 *balancer = NULL;
                 *worker = conf->forward;
                 access_status = OK;
+                /*
+                 * The forward worker does not keep connections alive, so
+                 * ensure that mod_proxy_http does the correct thing
+                 * regarding the Connection header in the request.
+                 */
+                apr_table_set(r->subprocess_env, "proxy-nokeepalive", "1");
             }
         }
         else if (r->proxyreq == PROXYREQ_REVERSE) {
             if (conf->reverse) {
                 ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                               "proxy: *: found reverse proxy worker for %s",
                                *url);
                 *balancer = NULL;
                 *worker = conf->reverse;
                 access_status = OK;
+                /*
+                 * The reverse worker does not keep connections alive, so
+                 * ensure that mod_proxy_http does the correct thing
+                 * regarding the Connection header in the request.
+                 */
+                apr_table_set(r->subprocess_env, "proxy-nokeepalive", "1");
             }
         }
     }
     else if (access_status == DECLINED && *balancer != NULL) {
         /* All the workers are busy */
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
