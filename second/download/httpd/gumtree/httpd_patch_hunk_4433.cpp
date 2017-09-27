     /* When the connection processing actually starts, we might 
      * take over, if the connection is for a task.
      */
     ap_hook_process_connection(h2_task_process_conn, 
                                NULL, NULL, APR_HOOK_FIRST);
 
-    ap_register_output_filter("H2_RESPONSE", h2_response_output_filter,
-                              NULL, AP_FTYPE_PROTOCOL);
-    ap_register_input_filter("H2_TO_H1", h2_filter_stream_input,
+    ap_register_input_filter("H2_SLAVE_IN", h2_filter_slave_in,
                              NULL, AP_FTYPE_NETWORK);
-    ap_register_output_filter("H1_TO_H2", h2_filter_stream_output,
+    ap_register_output_filter("H2_SLAVE_OUT", h2_filter_slave_output,
                               NULL, AP_FTYPE_NETWORK);
-    ap_register_output_filter("H1_TO_H2_RESP", h2_filter_read_response,
+    ap_register_output_filter("H2_PARSE_H1", h2_filter_parse_h1,
+                              NULL, AP_FTYPE_NETWORK);
+
+    ap_register_input_filter("H2_REQUEST", h2_filter_request_in,
+                             NULL, AP_FTYPE_PROTOCOL);
+    ap_register_output_filter("H2_RESPONSE", h2_filter_headers_out,
                               NULL, AP_FTYPE_PROTOCOL);
-    ap_register_output_filter("H2_TRAILERS", h2_response_trailers_filter,
+    ap_register_output_filter("H2_TRAILERS_OUT", h2_filter_trailers_out,
                               NULL, AP_FTYPE_PROTOCOL);
 }
 
 /* post config init */
 apr_status_t h2_task_init(apr_pool_t *pool, server_rec *s)
 {
