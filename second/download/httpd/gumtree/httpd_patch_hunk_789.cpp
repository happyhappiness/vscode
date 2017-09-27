 
         /* XXX: probably a better way to determine this */
         if (SSL_total_renegotiations(filter_ctx->pssl)) {
             reason = "likely due to failed renegotiation";
         }
 
-        ap_log_error(APLOG_MARK, APLOG_INFO, outctx->rc, c->base_server,
-                     "failed to write %d of %d bytes (%s)",
-                     len - (apr_size_t)res, len, reason);
+        ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c,
+                      "failed to write %" APR_SSIZE_T_FMT
+                      " of %" APR_SIZE_T_FMT " bytes (%s)",
+                      len - (apr_size_t)res, len, reason);
 
         outctx->rc = APR_EGENERAL;
     }
     return outctx->rc;
 }
 
