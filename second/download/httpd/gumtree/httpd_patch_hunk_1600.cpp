     ap_byterange_filter_handle =
         ap_register_output_filter("BYTERANGE", ap_byterange_filter,
                                   NULL, AP_FTYPE_PROTOCOL);
     ap_method_registry_init(p);
 }
 
-module AP_MODULE_DECLARE_DATA http_module = {
+AP_DECLARE_MODULE(http) = {
     STANDARD20_MODULE_STUFF,
     NULL,              /* create per-directory config structure */
     NULL,              /* merge per-directory config structures */
     NULL,              /* create per-server config structure */
     NULL,              /* merge per-server config structures */
     http_cmds,         /* command apr_table_t */
