         ERR_error_string_n(e, err, sizeof err);
         annotation = ssl_log_annotation(err);
 
         ap_log_error(file, line, APLOG_MODULE_INDEX, level, 0, s,
                      "SSL Library Error: %s%s%s%s%s%s",
                      /* %s */
-                     err, 
+                     err,
                      /* %s%s%s */
-                     data ? " (" : "", data ? data : "", data ? ")" : "", 
+                     data ? " (" : "", data ? data : "", data ? ")" : "",
                      /* %s%s */
                      annotation ? " -- " : "",
                      annotation ? annotation : "");
 
         /* Pop the error off the stack: */
         ERR_get_error();
     }
 }
 
-void ssl_log_cxerror(const char *file, int line, int level, 
-                     apr_status_t rv, conn_rec *c, X509 *cert,
-                     const char *format, ...)
+static void ssl_log_cert_error(const char *file, int line, int level,
+                               apr_status_t rv, const server_rec *s,
+                               const conn_rec *c, const request_rec *r,
+                               apr_pool_t *p, X509 *cert, const char *format,
+                               va_list ap)
 {
-    va_list ap;
     char buf[HUGE_STRING_LEN];
-    char *sname, *iname, *serial;
-    BIGNUM *bn;
-    
-    if (APLOG_IS_LEVEL(mySrvFromConn(c),level)) {
-        /* Bail early since the rest of this function is expensive. */
-        return;
-    }
+    int msglen, n;
+    char *name;
 
-    sname = X509_NAME_oneline(X509_get_subject_name(cert), NULL, 0);
-    iname = X509_NAME_oneline(X509_get_issuer_name(cert),  NULL, 0);
-    bn = ASN1_INTEGER_to_BN(X509_get_serialNumber(cert), NULL);
-    serial = bn && !BN_is_zero(bn) ? BN_bn2hex(bn) : NULL;
-    
-    va_start(ap, format);
     apr_vsnprintf(buf, sizeof buf, format, ap);
-    va_end(ap);
 
-    ap_log_cerror(file, line, APLOG_MODULE_INDEX, level, rv, c,
-                  "%s [subject: %s, issuer: %s, serial: %s]",
-                  buf,
-                  sname ? sname : "-unknown-",
-                  iname ? iname : "-unknown-",
-                  serial ? serial : "-unknown-");
+    msglen = strlen(buf);
+
+    if (cert) {
+        BIO *bio = BIO_new(BIO_s_mem());
+
+        if (bio) {
+            /*
+             * Limit the maximum length of the subject and issuer DN strings
+             * in the log message. 300 characters should always be sufficient
+             * for holding both the timestamp, module name, pid etc. stuff
+             * at the beginning of the line and the trailing information about
+             * serial, notbefore and notafter.
+             */
+            int maxdnlen = (HUGE_STRING_LEN - msglen - 300) / 2;
+
+            BIO_puts(bio, " [subject: ");
+            name = SSL_X509_NAME_to_string(p, X509_get_subject_name(cert),
+                                           maxdnlen);
+            if (!strIsEmpty(name)) {
+                BIO_puts(bio, name);
+            } else {
+                BIO_puts(bio, "-empty-");
+            }
+
+            BIO_puts(bio, " / issuer: ");
+            name = SSL_X509_NAME_to_string(p, X509_get_issuer_name(cert),
+                                           maxdnlen);
+            if (!strIsEmpty(name)) {
+                BIO_puts(bio, name);
+            } else {
+                BIO_puts(bio, "-empty-");
+            }
+
+            BIO_puts(bio, " / serial: ");
+            if (i2a_ASN1_INTEGER(bio, X509_get_serialNumber(cert)) == -1)
+                BIO_puts(bio, "(ERROR)");
+
+            BIO_puts(bio, " / notbefore: ");
+            ASN1_TIME_print(bio, X509_get_notBefore(cert));
+
+            BIO_puts(bio, " / notafter: ");
+            ASN1_TIME_print(bio, X509_get_notAfter(cert));
+
+            BIO_puts(bio, "]");
+
+            n = BIO_read(bio, buf + msglen, sizeof buf - msglen - 1);
+            if (n > 0)
+               buf[msglen + n] = '\0';
+
+            BIO_free(bio);
+        }
+    }
+    else {
+        apr_snprintf(buf + msglen, sizeof buf - msglen,
+                     " [certificate: -not available-]");
+    }
 
-    if (sname) {
-        modssl_free(sname);
+    if (r) {
+        ap_log_rerror(file, line, APLOG_MODULE_INDEX, level, rv, r, "%s", buf);
     }
-    
-    if (iname) {
-        modssl_free(iname);
+    else if (c) {
+        ap_log_cerror(file, line, APLOG_MODULE_INDEX, level, rv, c, "%s", buf);
     }
-    
-    if (serial) {
-        modssl_free(serial);
+    else if (s) {
+        ap_log_error(file, line, APLOG_MODULE_INDEX, level, rv, s, "%s", buf);
     }
 
-    if (bn) {
-        BN_free(bn);
+}
+
+/*
+ * Wrappers for ap_log_error/ap_log_cerror/ap_log_rerror which log additional
+ * details of the X509 cert. For ssl_log_xerror, a pool needs to be passed in
+ * as well (for temporary allocation of the cert's subject/issuer name strings,
+ * in the other cases we use the connection and request pool, respectively).
+ */
+void ssl_log_xerror(const char *file, int line, int level, apr_status_t rv,
+                    apr_pool_t *ptemp, server_rec *s, X509 *cert,
+                    const char *fmt, ...)
+{
+    if (APLOG_IS_LEVEL(s,level)) {
+       va_list ap;
+       va_start(ap, fmt);
+       ssl_log_cert_error(file, line, level, rv, s, NULL, NULL, ptemp,
+                          cert, fmt, ap);
+       va_end(ap);
+    }
+}
+
+void ssl_log_cxerror(const char *file, int line, int level, apr_status_t rv,
+                     conn_rec *c, X509 *cert, const char *fmt, ...)
+{
+    if (APLOG_IS_LEVEL(mySrvFromConn(c),level)) {
+       va_list ap;
+       va_start(ap, fmt);
+       ssl_log_cert_error(file, line, level, rv, NULL, c, NULL, c->pool,
+                          cert, fmt, ap);
+       va_end(ap);
+    }
+}
+
+void ssl_log_rxerror(const char *file, int line, int level, apr_status_t rv,
+                     request_rec *r, X509 *cert, const char *fmt, ...)
+{
+    if (APLOG_R_IS_LEVEL(r,level)) {
+       va_list ap;
+       va_start(ap, fmt);
+       ssl_log_cert_error(file, line, level, rv, NULL, NULL, r, r->pool,
+                          cert, fmt, ap);
+       va_end(ap);
     }
 }
