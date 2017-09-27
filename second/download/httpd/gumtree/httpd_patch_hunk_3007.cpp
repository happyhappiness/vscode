             rv = get_data(conn, (char *) farray, &readbuflen);
             if (rv != APR_SUCCESS) {
                 break;
             }
 
             dump_header_to_log(r, farray, readbuflen);
-            
+
             if (readbuflen != FCGI_HEADER_LEN) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                             "proxy: FCGI: Failed to read entire header "
-                             "got %" APR_SIZE_T_FMT " wanted %d", 
-                             readbuflen, FCGI_HEADER_LEN);
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01067)
+                              "Failed to read entire header "
+                              "got %" APR_SIZE_T_FMT " wanted %d",
+                              readbuflen, FCGI_HEADER_LEN);
                 rv = APR_EINVAL;
                 break;
             }
 
             fcgi_header_from_array(&header, farray);
 
             if (header.version != FCGI_VERSION) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                             "proxy: FCGI: Got bogus version %d",
-                             (int) header.version);
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01068)
+                              "Got bogus version %d", (int) header.version);
                 rv = APR_EINVAL;
                 break;
             }
 
             type = header.type;
 
             rid = header.requestIdB1 << 8;
             rid |= header.requestIdB0;
 
             if (rid != request_id) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                             "proxy: FCGI: Got bogus rid %d, expected %d",
-                             rid, request_id);
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01069)
+                              "Got bogus rid %d, expected %d",
+                              rid, request_id);
                 rv = APR_EINVAL;
                 break;
             }
 
             clen = header.contentLengthB1 << 8;
             clen |= header.contentLengthB0;
