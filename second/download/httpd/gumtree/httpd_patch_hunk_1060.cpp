     ap_http_header_filter_handle =
         ap_register_output_filter("HTTP_HEADER", ap_http_header_filter,
                                   NULL, AP_FTYPE_PROTOCOL);
     ap_chunk_filter_handle =
         ap_register_output_filter("CHUNK", ap_http_chunk_filter,
                                   NULL, AP_FTYPE_TRANSCODE);
+    ap_http_outerror_filter_handle =
+        ap_register_output_filter("HTTP_OUTERROR", ap_http_outerror_filter,
+                                  NULL, AP_FTYPE_PROTOCOL);
     ap_byterange_filter_handle =
         ap_register_output_filter("BYTERANGE", ap_byterange_filter,
                                   NULL, AP_FTYPE_PROTOCOL);
     ap_method_registry_init(p);
 }
 
