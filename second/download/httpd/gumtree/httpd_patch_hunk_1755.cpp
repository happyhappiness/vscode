     ap_register_input_filter(logio_filter_name, logio_in_filter, NULL,
                              AP_FTYPE_NETWORK - 1);
     ap_register_output_filter(logio_filter_name, logio_out_filter, NULL,
                               AP_FTYPE_NETWORK - 1);
 
     APR_REGISTER_OPTIONAL_FN(ap_logio_add_bytes_out);
+    APR_REGISTER_OPTIONAL_FN(ap_logio_add_bytes_in);
 }
 
 module AP_MODULE_DECLARE_DATA logio_module =
 {
     STANDARD20_MODULE_STUFF,
     NULL,                       /* create per-dir config */
