             if (rv == 0) {
                 group = apr_array_push(groups);
                 *group = apr_dbd_get_entry(dbd->driver, row, 0);
             }
             else {
                 message = apr_dbd_error(dbd->driver, dbd->handle, rv);
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01651)
                         "authz_dbd in get_row; group query for user=%s [%s]",
                         r->user, message?message:noerror);
                 return HTTP_INTERNAL_SERVER_ERROR;
             }
         }
     }
     else {
         message = apr_dbd_error(dbd->driver, dbd->handle, rv);
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01652)
                       "authz_dbd, in groups query for %s [%s]",
                       r->user, message?message:noerror);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
     return OK;
 }
 
 static authz_status dbdgroup_check_authorization(request_rec *r,
-                                              const char *require_args)
+                                                 const char *require_args,
+                                                 const void *parsed_require_args)
 {
     int i, rv;
     const char *w;
     apr_array_header_t *groups = NULL;
     const char *t;
     authz_dbd_cfg *cfg = ap_get_module_config(r->per_dir_config,
