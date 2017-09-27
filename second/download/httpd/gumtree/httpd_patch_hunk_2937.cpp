         }
 
         if ((name & 0XFF00) == 0XA000) {
             ajp_msg_get_uint16(msg, &name);
             stringname = long_res_header_for_sc(name);
             if (stringname == NULL) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00984)
                        "ajp_unmarshal_response: "
                        "No such sc (%08x)",
                        name);
                 return AJP_EBAD_HEADER;
             }
         } else {
             name = 0;
             rc = ajp_msg_get_string(msg, &stringname);
             if (rc != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00985)
                        "ajp_unmarshal_response: "
                        "Null header name");
                 return rc;
             }
             ap_xlate_proto_from_ascii(stringname, strlen(stringname));
         }
 
         rc = ajp_msg_get_string(msg, &value);
         if (rc != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00986)
                    "ajp_unmarshal_response: "
                    "Null header value");
             return rc;
         }
 
         /* Set-Cookie need additional processing */
