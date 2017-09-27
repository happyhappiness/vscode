 
     from.pool = p;
 
     rv = apr_socket_recvfrom(&from, ctx->sock, 0, buf, &len);
 
     if (APR_STATUS_IS_EAGAIN(rv)) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
-                     "Heartmonitor: would block");
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02088) "would block");
         return APR_SUCCESS;
     }
     else if (rv) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
-                     "Heartmonitor: recvfrom failed");
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s, APLOGNO(02089) "recvfrom failed");
         return rv;
     }
 
     hm_processmsg(ctx, p, &from, buf, len);
 
     return rv;
