     }
 
     apr_brigade_cleanup(bb);
     return APR_SUCCESS;
 }
 
+static int mod_deflate_post_config(apr_pool_t *pconf, apr_pool_t *plog,
+                                   apr_pool_t *ptemp, server_rec *s)
+{
+    mod_deflate_ssl_var = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
+    return OK;
+}
+
+
 #define PROTO_FLAGS AP_FILTER_PROTO_CHANGE|AP_FILTER_PROTO_CHANGE_LENGTH
 static void register_hooks(apr_pool_t *p)
 {
     ap_register_output_filter(deflateFilterName, deflate_out_filter, NULL,
                               AP_FTYPE_CONTENT_SET);
     ap_register_output_filter("INFLATE", inflate_out_filter, NULL,
                               AP_FTYPE_RESOURCE-1);
     ap_register_input_filter(deflateFilterName, deflate_in_filter, NULL,
                               AP_FTYPE_CONTENT_SET);
+    ap_hook_post_config(mod_deflate_post_config, NULL, NULL, APR_HOOK_MIDDLE);
 }
 
 static const command_rec deflate_filter_cmds[] = {
     AP_INIT_TAKE12("DeflateFilterNote", deflate_set_note, NULL, RSRC_CONF,
                   "Set a note to report on compression ratio"),
     AP_INIT_TAKE1("DeflateWindowSize", deflate_set_window_size, NULL,
