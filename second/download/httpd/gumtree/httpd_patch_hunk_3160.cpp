     return;
 }
 
 void ssl_io_filter_register(apr_pool_t *p)
 {
     ap_register_input_filter  (ssl_io_filter, ssl_io_filter_input,  NULL, AP_FTYPE_CONNECTION + 5);
+    ap_register_output_filter (ssl_io_coalesce, ssl_io_filter_coalesce, NULL, AP_FTYPE_CONNECTION + 4);
     ap_register_output_filter (ssl_io_filter, ssl_io_filter_output, NULL, AP_FTYPE_CONNECTION + 5);
 
     ap_register_input_filter  (ssl_io_buffer, ssl_io_filter_buffer, NULL, AP_FTYPE_PROTOCOL);
 
     return;
 }
