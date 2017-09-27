     }
 
 /* XXXX need to figure out how to do this
     if (s->secret) {
         if (ajp_msg_append_uint8(msg, SC_A_SECRET) ||
             ajp_msg_append_string(msg, s->secret)) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(03228)
                    "Error ajp_marshal_into_msgb - "
                    "Error appending secret");
             return APR_EGENERAL;
         }
     }
  */
