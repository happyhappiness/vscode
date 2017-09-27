 
             case FCGI_END_REQUEST:
                 done = 1;
                 break;
 
             default:
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                             "proxy: FCGI: Got bogus record %d", type);
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01072)
+                              "Got bogus record %d", type);
                 break;
             }
 
             if (plen) {
                 readbuflen = plen;
 
