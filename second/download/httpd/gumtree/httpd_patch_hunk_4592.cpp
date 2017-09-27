                 next_request(ctx, 1); 
                 h2_proxy_session_cancel_all(ctx->session);
                 h2_proxy_session_process(ctx->session);
                 status = ctx->r_status = APR_SUCCESS;
                 break;
             }
-            if (!ctx->next && h2_proxy_ihash_empty(ctx->session->streams)) {
+            if ((h2_proxy_fifo_count(ctx->requests) == 0) 
+                && h2_proxy_ihash_empty(ctx->session->streams)) {
                 break;
             }
         }
         else {
             /* end of processing, maybe error */
             ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, ctx->owner, 
