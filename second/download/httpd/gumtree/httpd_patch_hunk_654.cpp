                       "Digest: unknown algorithm `%s' received: %s",
                       resp->algorithm, r->uri);
         note_digest_auth_failure(r, conf, resp, 0);
         return HTTP_UNAUTHORIZED;
     }
 
-    if (!conf->pwfile) {
-        return DECLINED;
-    }
+    return_code = get_hash(r, r->user, conf);
 
-    if (!(conf->ha1 = get_hash(r, r->user, conf->realm, conf->pwfile))) {
+    if (return_code == AUTH_USER_NOT_FOUND) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                       "Digest: user `%s' in realm `%s' not found: %s",
                       r->user, conf->realm, r->uri);
         note_digest_auth_failure(r, conf, resp, 0);
         return HTTP_UNAUTHORIZED;
     }
+    else if (return_code == AUTH_USER_FOUND) {
+        /* we have a password, so continue */
+    }
+    else if (return_code == AUTH_DENIED) {
+        /* authentication denied in the provider before attempting a match */
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                      "Digest: user `%s' in realm `%s' denied by provider: %s",
+                      r->user, conf->realm, r->uri);
+        note_digest_auth_failure(r, conf, resp, 0);
+        return HTTP_UNAUTHORIZED;
+    }
+    else {
+        /* AUTH_GENERAL_ERROR (or worse)
+         * We'll assume that the module has already said what its error
+         * was in the logs.
+         */
+        return HTTP_INTERNAL_SERVER_ERROR;
+    }
 
-    
     if (resp->message_qop == NULL) {
         /* old (rfc-2069) style digest */
         if (strcmp(resp->digest, old_digest(r, resp, conf->ha1))) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "Digest: user %s: password mismatch: %s", r->user,
                           r->uri);
