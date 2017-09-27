         }
 
         tenc = apr_table_get(f->r->headers_in, "Transfer-Encoding");
         lenp = apr_table_get(f->r->headers_in, "Content-Length");
 
         if (tenc) {
-            if (!strcasecmp(tenc, "chunked")) {
+            if (strcasecmp(tenc, "chunked") == 0 /* fast path */
+                    || ap_find_last_token(f->r->pool, tenc, "chunked")) {
                 ctx->state = BODY_CHUNK;
             }
-            /* test lenp, because it gives another case we can handle */
-            else if (!lenp) {
-                /* Something that isn't in HTTP, unless some future
-                 * edition defines new transfer encodings, is unsupported.
+            else if (f->r->proxyreq == PROXYREQ_RESPONSE) {
+                /* http://tools.ietf.org/html/draft-ietf-httpbis-p1-messaging-23
+                 * Section 3.3.3.3: "If a Transfer-Encoding header field is
+                 * present in a response and the chunked transfer coding is not
+                 * the final encoding, the message body length is determined by
+                 * reading the connection until it is closed by the server."
                  */
+                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(02555)
+                              "Unknown Transfer-Encoding: %s;"
+                              " using read-until-close", tenc);
+                tenc = NULL;
+            }
+            else {
                 ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(01585)
                               "Unknown Transfer-Encoding: %s", tenc);
                 return bail_out_on_error(ctx, f, HTTP_NOT_IMPLEMENTED);
             }
-            else {
-                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r, APLOGNO(01586)
-                  "Unknown Transfer-Encoding: %s; using Content-Length", tenc);
-                tenc = NULL;
-            }
+            lenp = NULL;
         }
-        if (lenp && !tenc) {
+        if (lenp) {
             char *endstr;
 
             ctx->state = BODY_LENGTH;
 
             /* Protects against over/underflow, non-digit chars in the
              * string (excluding leading space) (the endstr checks)
