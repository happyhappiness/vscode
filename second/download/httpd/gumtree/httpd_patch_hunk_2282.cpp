 
     auth_result = apply_authz_sections(r, conf->section, AUTHZ_LOGIC_AND);
 
     if (auth_result == AUTHZ_GRANTED) {
         return OK;
     }
+    else if (auth_result == AUTHZ_DENIED_NO_USER) {
+        if (after_authn) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
+                          "authorization failure (no authenticated user): %s",
+                          r->uri);
+            /*
+             * If we're returning 401 to an authenticated user, tell them to
+             * try again. If unauthenticated, note_auth_failure has already
+             * been called during auth.
+             */
+            if (r->user)
+                ap_note_auth_failure(r);
+
+            return HTTP_UNAUTHORIZED;
+        }
+        else {
+            /*
+             * We need a user before we can decide what to do.
+             * Get out of the way and proceed with authentication.
+             */
+            return DECLINED;
+        }
+    }
     else if (auth_result == AUTHZ_DENIED || auth_result == AUTHZ_NEUTRAL) {
-        if (r->ap_auth_type == NULL) {
+        if (!after_authn || ap_auth_type(r) == NULL) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
                           "client denied by server configuration: %s%s",
                           r->filename ? "" : "uri ",
                           r->filename ? r->filename : r->uri);
 
             return HTTP_FORBIDDEN;
         }
         else {
+            /* XXX: maybe we want to return FORBIDDEN here, too??? */
             ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
                           "user %s: authorization failure for \"%s\": ",
                           r->user, r->uri);
 
-            /* If we're returning 403, tell them to try again. */
-            ap_note_auth_failure(r);
+            /*
+             * If we're returning 401 to an authenticated user, tell them to
+             * try again. If unauthenticated, note_auth_failure has already
+             * been called during auth.
+             */
+            if (r->user)
+                ap_note_auth_failure(r);
 
             return HTTP_UNAUTHORIZED;
         }
     }
     else {
         /* We'll assume that the module has already said what its
          * error was in the logs.
          */
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 }
 
+static int authorize_userless(request_rec *r)
+{
+    return authorize_user_core(r, 0);
+}
+
+static int authorize_user(request_rec *r)
+{
+    return authorize_user_core(r, 1);
+}
+
 static int authz_some_auth_required(request_rec *r)
 {
     authz_core_dir_conf *conf;
 
     conf = ap_get_module_config(r->per_dir_config, &authz_core_module);
 
