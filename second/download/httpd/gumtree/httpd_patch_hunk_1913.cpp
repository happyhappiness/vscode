         ap_note_basic_auth_failure(r);
         return HTTP_UNAUTHORIZED;
     }
 
     if (strcasecmp(ap_getword(r->pool, &auth_line, ' '), "Basic")) {
         /* Client tried to authenticate using wrong auth scheme */
-        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                       "client used wrong authentication scheme: %s", r->uri);
         ap_note_basic_auth_failure(r);
         return HTTP_UNAUTHORIZED;
     }
 
     while (*auth_line == ' ' || *auth_line == '\t') {
         auth_line++;
     }
 
     t = ap_pbase64decode(r->pool, auth_line);
     r->user = ap_getword_nulls (r->pool, &t, ':');
-    apr_table_setn(r->notes, AP_GET_BASIC_AUTH_PW_NOTE, "1");
     r->ap_auth_type = "Basic";
 
     *pw = t;
 
     return OK;
 }
 
-AP_DECLARE(apr_status_t) ap_get_basic_auth_components(const request_rec *r,
-                                                      const char **username,
-                                                      const char **password)
-{
-    const char *auth_header;
-    const char *credentials;
-    const char *decoded;
-    const char *user;
-
-    auth_header = (PROXYREQ_PROXY == r->proxyreq) ? "Proxy-Authorization"
-                                                  : "Authorization";
-    credentials = apr_table_get(r->headers_in, auth_header);
-
-    if (!credentials) {
-        /* No auth header. */
-        return APR_EINVAL;
-    }
-
-    if (strcasecmp(ap_getword(r->pool, &credentials, ' '), "Basic")) {
-        /* These aren't Basic credentials. */
-        return APR_EINVAL;
-    }
-
-    while (*credentials == ' ' || *credentials == '\t') {
-        credentials++;
-    }
-
-    /* XXX Our base64 decoding functions don't actually error out if the string
-     * we give it isn't base64; they'll just silently stop and hand us whatever
-     * they've parsed up to that point.
-     *
-     * Since this function is supposed to be a drop-in replacement for the
-     * deprecated ap_get_basic_auth_pw(), don't fix this for 2.4.x.
-     */
-    decoded = ap_pbase64decode(r->pool, credentials);
-    user = ap_getword_nulls(r->pool, &decoded, ':');
-
-    if (username) {
-        *username = user;
-    }
-    if (password) {
-        *password = decoded;
-    }
-
-    return APR_SUCCESS;
-}
-
 struct content_length_ctx {
     int data_sent;  /* true if the C-L filter has already sent at
                      * least one bucket on to the next output filter
                      * for this request
                      */
+    apr_bucket_brigade *tmpbb;
 };
 
 /* This filter computes the content length, but it also computes the number
  * of bytes sent to the client.  This means that this filter will always run
  * through all of the buckets in all brigades
  */
