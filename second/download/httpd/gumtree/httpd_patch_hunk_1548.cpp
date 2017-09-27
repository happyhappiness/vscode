             b = apr_bucket_transient_create(shi->pszHeader + ate,
                                             shi->cchHeader - ate,
                                             c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bb, b);
             b = apr_bucket_flush_create(c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bb, b);
-            ap_pass_brigade(cid->r->output_filters, bb);
+            rv = ap_pass_brigade(cid->r->output_filters, bb);
             cid->response_sent = 1;
-        }
+            if (rv != APR_SUCCESS)
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
+                              "ISAPI: ServerSupport function "
+                              "HSE_REQ_SEND_RESPONSE_HEADER_EX "
+                              "ap_pass_brigade failed: %s", r->filename);
+            return (rv == APR_SUCCESS);
+        }
+        /* Deliberately hold off sending 'just the headers' to begin to
+         * accumulate the body and speed up the overall response, or at
+         * least wait for the end the session.
+         */
         return 1;
     }
 
     case HSE_REQ_CLOSE_CONNECTION:  /* Added after ISAPI 4.0 */
         if (cid->dconf.log_unsupported)
             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
