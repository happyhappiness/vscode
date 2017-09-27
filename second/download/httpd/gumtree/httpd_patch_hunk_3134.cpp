 static void ssl_check_public_cert(server_rec *s,
                                   apr_pool_t *ptemp,
                                   X509 *cert,
                                   int type)
 {
     int is_ca, pathlen;
-    char *cn;
+    apr_array_header_t *ids;
 
     if (!cert) {
         return;
     }
 
     /*
      * Some information about the certificate(s)
      */
 
     if (SSL_X509_isSGC(cert)) {
-        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01905)
                      "%s server certificate enables "
                      "Server Gated Cryptography (SGC)",
                      ssl_asn1_keystr(type));
     }
 
     if (SSL_X509_getBC(cert, &is_ca, &pathlen)) {
         if (is_ca) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01906)
                          "%s server certificate is a CA certificate "
                          "(BasicConstraints: CA == TRUE !?)",
                          ssl_asn1_keystr(type));
         }
 
         if (pathlen > 0) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01907)
                          "%s server certificate is not a leaf certificate "
                          "(BasicConstraints: pathlen == %d > 0 !?)",
                          ssl_asn1_keystr(type), pathlen);
         }
     }
 
-    if (SSL_X509_getCN(ptemp, cert, &cn)) {
-        int fnm_flags = APR_FNM_PERIOD|APR_FNM_CASE_BLIND;
-
-        if (apr_fnmatch_test(cn)) {
-            if (apr_fnmatch(cn, s->server_hostname,
-                            fnm_flags) == APR_FNM_NOMATCH) {
-                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
-                             "%s server certificate wildcard CommonName "
-                             "(CN) `%s' does NOT match server name!?",
-                             ssl_asn1_keystr(type), cn);
+    /*
+     * Check if the server name is covered by the certificate.
+     * Consider both dNSName entries in the subjectAltName extension
+     * and, as a fallback, commonName attributes in the subject DN.
+     * (DNS-IDs and CN-IDs as defined in RFC 6125).
+     */
+    if (SSL_X509_getIDs(ptemp, cert, &ids)) {
+        char *cp;
+        int i;
+        char **id = (char **)ids->elts;
+        BOOL is_wildcard, matched = FALSE;
+
+        for (i = 0; i < ids->nelts; i++) {
+            if (!id[i])
+                continue;
+
+            /*
+             * Determine if it is a wildcard ID - we're restrictive
+             * in the sense that we require the wildcard character to be
+             * THE left-most label (i.e., the ID must start with "*.")
+             */
+            is_wildcard = (*id[i] == '*' && *(id[i]+1) == '.') ? TRUE : FALSE;
+
+            /*
+             * If the ID includes a wildcard character, check if it matches
+             * for the left-most DNS label (i.e., the wildcard character
+             * is not allowed to match a dot). Otherwise, try a simple
+             * string compare, case insensitively.
+             */
+            if ((is_wildcard == TRUE &&
+                 (cp = strchr(s->server_hostname, '.')) &&
+                 !strcasecmp(id[i]+1, cp)) ||
+                !strcasecmp(id[i], s->server_hostname)) {
+                matched = TRUE;
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01908)
+                             "%sID '%s' in %s certificate configured "
+                             "for %s matches server name",
+                             is_wildcard ? "Wildcard " : "",
+                             id[i], ssl_asn1_keystr(type),
+                             (mySrvConfig(s))->vhost_id);
+                break;
             }
         }
-        else if (strNE(s->server_hostname, cn)) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
-                         "%s server certificate CommonName (CN) `%s' "
-                         "does NOT match server name!?",
-                         ssl_asn1_keystr(type), cn);
+
+        if (matched == FALSE) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01909)
+                         "%s certificate configured for %s does NOT include "
+                         "an ID which matches the server name",
+                         ssl_asn1_keystr(type), (mySrvConfig(s))->vhost_id);
         }
     }
 }
 
 static void ssl_init_server_certs(server_rec *s,
                                   apr_pool_t *p,
