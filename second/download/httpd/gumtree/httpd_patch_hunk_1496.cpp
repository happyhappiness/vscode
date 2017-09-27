     if (!ap_auth_name(r)) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR,
                       0, r, "need AuthName: %s", r->uri);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
-    r->ap_auth_type = "Basic";
+    r->ap_auth_type = (char*)current_auth;
 
     res = get_basic_auth(r, &sent_user, &sent_pw);
     if (res) {
         return res;
     }
 
