
    return OK;
}

static void register_hooks(apr_pool_t *p)
{
    ap_hook_process_connection(ap_process_http_connection,NULL,NULL,
			       APR_HOOK_REALLY_LAST);
    ap_hook_map_to_storage(ap_send_http_trace,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_http_method(http_method,NULL,NULL,APR_HOOK_REALLY_LAST);
    ap_hook_default_port(http_port,NULL,NULL,APR_HOOK_REALLY_LAST);
    ap_hook_create_request(http_create_request, NULL, NULL, APR_HOOK_REALLY_LAST);
    ap_http_input_filter_handle =
        ap_register_input_filter("HTTP_IN", ap_http_filter,
                                 NULL, AP_FTYPE_PROTOCOL);
    ap_http_header_filter_handle =
        ap_register_output_filter("HTTP_HEADER", ap_http_header_filter, 
                                  NULL, AP_FTYPE_PROTOCOL);
    ap_chunk_filter_handle =
        ap_register_output_filter("CHUNK", chunk_filter,
                                  NULL, AP_FTYPE_TRANSCODE);
    ap_byterange_filter_handle =
        ap_register_output_filter("BYTERANGE", ap_byterange_filter,
                                  NULL, AP_FTYPE_PROTOCOL);
    ap_method_registry_init(p);
}

module AP_MODULE_DECLARE_DATA http_module = {
    STANDARD20_MODULE_STUFF,
    NULL,			/* create per-directory config structure */
    NULL,			/* merge per-directory config structures */
    NULL,			/* create per-server config structure */
    NULL,			/* merge per-server config structures */
    http_cmds,			/* command apr_table_t */
    register_hooks		/* register hooks */
};
