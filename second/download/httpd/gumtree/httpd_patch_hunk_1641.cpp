     const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "Into ajp_marshal_into_msgb");
 
     if ((method = sc_for_req_method_by_id(r)) == UNKNOWN_METHOD) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-               "ajp_marshal_into_msgb - Sending unknown method %s as request attribute",
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+               "ajp_marshal_into_msgb - No such method %s",
                r->method);
-        method = SC_M_JK_STORED;
+        return AJP_EBAD_METHOD;
     }
 
     is_ssl = (apr_byte_t) ap_proxy_conn_is_https(r->connection);
 
     if (r->headers_in && apr_table_elts(r->headers_in)) {
         const apr_array_header_t *t = apr_table_elts(r->headers_in);
