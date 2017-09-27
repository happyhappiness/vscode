             /* Protects against over/underflow, non-digit chars in the
              * string (excluding leading space) (the endstr checks)
              * and a negative number. */
             if (apr_strtoff(&ctx->remaining, lenp, &endstr, 10)
                 || endstr == lenp || *endstr || ctx->remaining < 0) {
 
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(01411)
                               "Invalid Content-Length");
 
                 ap_remove_input_filter(f);
                 return bail_out_on_error(b, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
             }
 
             /* If we have a limit in effect and we know the C-L ahead of
              * time, stop it here if it is invalid.
              */
             if (dconf->keep_body < ctx->remaining) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(01412)
                           "Requested content-length of %" APR_OFF_T_FMT
                           " is larger than the configured limit"
                           " of %" APR_OFF_T_FMT, ctx->remaining, dconf->keep_body);
                 ap_remove_input_filter(f);
                 return bail_out_on_error(b, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
             }
