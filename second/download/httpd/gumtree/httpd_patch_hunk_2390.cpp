         if (!(conf->authoritative) && auth_result != AUTH_DENIED) {
             return DECLINED;
         }
 
         switch (auth_result) {
         case AUTH_DENIED:
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01617)
                       "user %s: authentication failure for \"%s\": "
                       "Password Mismatch",
                       sent_user, r->uri);
             return_code = HTTP_UNAUTHORIZED;
             break;
         case AUTH_USER_NOT_FOUND:
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01618)
                       "user %s not found: %s", sent_user, r->uri);
             return_code = HTTP_UNAUTHORIZED;
             break;
         case AUTH_GENERAL_ERROR:
         default:
             /* We'll assume that the module has already said what its error
