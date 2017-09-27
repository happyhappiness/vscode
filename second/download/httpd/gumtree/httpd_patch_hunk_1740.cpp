      */
     ap_register_output_filter ("UPGRADE_FILTER", ssl_io_filter_Upgrade, NULL, AP_FTYPE_PROTOCOL + 5);
 
     ap_register_input_filter  (ssl_io_filter, ssl_io_filter_input,  NULL, AP_FTYPE_CONNECTION + 5);
     ap_register_output_filter (ssl_io_filter, ssl_io_filter_output, NULL, AP_FTYPE_CONNECTION + 5);
 
-    ap_register_input_filter  (ssl_io_buffer, ssl_io_filter_buffer, NULL, AP_FTYPE_PROTOCOL - 1);
+    ap_register_input_filter  (ssl_io_buffer, ssl_io_filter_buffer, NULL, AP_FTYPE_PROTOCOL);
 
     return;
 }
 
 /*  _________________________________________________________________
 **
