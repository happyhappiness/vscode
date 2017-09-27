                 apr_pstrcat(p, "Corrupt status line returned by remote "
                             "server: ", buffer, NULL));
             }
             backasswards = 0;
 
             keepchar = buffer[12];
-            if (keepchar == '\0') {
-                ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
-                             r->server, "proxy: bad HTTP/%d.%d status line "
-                             "returned by %s (%s)", major, minor, r->uri,
-                             r->method);
-            }
             buffer[12] = '\0';
             r->status = atoi(&buffer[9]);
 
-            buffer[12] = keepchar;
+            if (keepchar != '\0') {
+                buffer[12] = keepchar;
+            } else {
+                /* 2616 requires the space in Status-Line; the origin
+                 * server may have sent one but ap_rgetline_core will
+                 * have stripped it. */
+                buffer[12] = ' ';
+                buffer[13] = '\0';
+            }
             r->status_line = apr_pstrdup(p, &buffer[9]);
             
 
             /* read the headers. */
             /* N.B. for HTTP/1.0 clients, we have to fold line-wrapped headers*/
             /* Also, take care with headers with multiple occurences. */
