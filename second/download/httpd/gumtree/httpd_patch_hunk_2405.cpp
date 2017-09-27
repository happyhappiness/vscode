         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     if (resp->message_qop == NULL) {
         /* old (rfc-2069) style digest */
         if (strcmp(resp->digest, old_digest(r, resp, conf->ha1))) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                          "Digest: user %s: password mismatch: %s", r->user,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01792)
+                          "user %s: password mismatch: %s", r->user,
                           r->uri);
             note_digest_auth_failure(r, conf, resp, 0);
             return HTTP_UNAUTHORIZED;
         }
     }
     else {
