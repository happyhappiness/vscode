                           "ajp_marshal_into_msgb: "
                           "Error appending the method '%s' as request attribute",
                           r->method);
             return AJP_EOVERFLOW;
         }
     }
+    /* Forward the SSL protocol name.
+     * Modern Tomcat versions know how to retrieve
+     * the protocol name from this attribute.
+     */
+    if (is_ssl) {
+        if ((envvar = ap_proxy_ssl_val(r->pool, r->server, r->connection, r,
+                                       AJP13_SSL_PROTOCOL_INDICATOR))
+            && envvar[0]) {
+            const char *key = SC_A_SSL_PROTOCOL;
+            if (ajp_msg_append_uint8(msg, SC_A_REQ_ATTRIBUTE) ||
+                ajp_msg_append_string(msg, key)   ||
+                ajp_msg_append_string(msg, envvar)) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02830)
+                        "ajp_marshal_into_msgb: "
+                        "Error appending attribute %s=%s",
+                        key, envvar);
+                return AJP_EOVERFLOW;
+            }
+        }
+    }
     /* Forward the remote port information, which was forgotten
      * from the builtin data of the AJP 13 protocol.
      * Since the servlet spec allows to retrieve it via getRemotePort(),
      * we provide the port to the Tomcat connector as a request
      * attribute. Modern Tomcat versions know how to retrieve
      * the remote port from this attribute.
