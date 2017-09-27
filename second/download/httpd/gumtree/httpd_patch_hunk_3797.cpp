                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00984)
                        "ajp_unmarshal_response: "
                        "No such sc (%08x)",
                        name);
                 return AJP_EBAD_HEADER;
             }
-        } else {
+        }
+        else {
             name = 0;
             rc = ajp_msg_get_string(msg, &stringname);
             if (rc != APR_SUCCESS) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00985)
                        "ajp_unmarshal_response: "
                        "Null header name");
