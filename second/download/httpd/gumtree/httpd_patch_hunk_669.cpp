         if (data_type)
             headlen = strlen((char*) data_type);
         ate = send_response_header(cid, (char*) buf_data,
                                    (char*) data_type,
                                    statlen, headlen);
         if (ate < 0) {
-            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
+            SetLastError(ERROR_INVALID_PARAMETER);
             return 0;
         }
         else if ((apr_size_t)ate < headlen) {
             apr_bucket_brigade *bb;
             apr_bucket *b;
             bb = apr_brigade_create(cid->r->pool, c->bucket_alloc);
             b = apr_bucket_transient_create((char*) data_type + ate,
                                            headlen - ate, c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bb, b);
             b = apr_bucket_flush_create(c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bb, b);
-            rv = ap_pass_brigade(cid->r->output_filters, bb);
+            ap_pass_brigade(cid->r->output_filters, bb);
             cid->response_sent = 1;
-            if (rv != APR_SUCCESS)
-                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
-                              "ISAPI: ServerSupport function "
-                              "HSE_REQ_SEND_RESPONSE_HEADER "
-                              "ap_pass_brigade failed: %s", r->filename);
-            return (rv == APR_SUCCESS);
-        }
-        /* Deliberately hold off sending 'just the headers' to begin to
-         * accumulate the body and speed up the overall response, or at
-         * least wait for the end the session.
-         */
+        }
         return 1;
     }
 
     case HSE_REQ_DONE_WITH_SESSION:
         /* Signal to resume the thread completing this request,
          * leave it to the pool cleanup to dispose of our mutex.
