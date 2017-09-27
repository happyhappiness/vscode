                 }
                 else {
                     return 0;
                 }
             }
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
-                    "Websocket: Reading %lu (%s) bytes, masking is %s. %s", 
+                    "Websocket: Reading %" APR_SIZE_T_FMT " (%s) bytes, masking is %s. %s", 
                     plen,
                     (payload >= 126) ? "extra payload" : "no extra payload", 
                     mask ? "on" : "off", 
                     fin ? "This is a final frame" : "more to follow");
             if (mask) {
                 len = 4;
