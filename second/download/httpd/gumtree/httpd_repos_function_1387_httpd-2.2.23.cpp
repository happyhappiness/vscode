static void register_hooks(apr_pool_t *p)
{
    /**
     * If we ae using an MPM That Supports Async Connections,
     * use a different processing function
     */
    int async_mpm = 0;
    if (ap_mpm_query(AP_MPMQ_IS_ASYNC, &async_mpm) == APR_SUCCESS
        && async_mpm == 1) {
        ap_hook_process_connection(ap_process_http_async_connection, NULL,
                                   NULL, APR_HOOK_REALLY_LAST);
    }
    else {
        ap_hook_process_connection(ap_process_http_connection, NULL, NULL,
                                   APR_HOOK_REALLY_LAST);
    }

    ap_hook_map_to_storage(ap_send_http_trace,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_map_to_storage(http_send_options,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_http_scheme(http_scheme,NULL,NULL,APR_HOOK_REALLY_LAST);
    ap_hook_default_port(http_port,NULL,NULL,APR_HOOK_REALLY_LAST);
    ap_hook_create_request(http_create_request, NULL, NULL, APR_HOOK_REALLY_LAST);
    ap_http_input_filter_handle =
        ap_register_input_filter("HTTP_IN", ap_http_filter,
                                 NULL, AP_FTYPE_PROTOCOL);
    ap_http_header_filter_handle =
        ap_register_output_filter("HTTP_HEADER", ap_http_header_filter,
                                  NULL, AP_FTYPE_PROTOCOL);
    ap_chunk_filter_handle =
        ap_register_output_filter("CHUNK", ap_http_chunk_filter,
                                  NULL, AP_FTYPE_TRANSCODE);
    ap_http_outerror_filter_handle =
        ap_register_output_filter("HTTP_OUTERROR", ap_http_outerror_filter,
                                  NULL, AP_FTYPE_PROTOCOL);
    ap_byterange_filter_handle =
        ap_register_output_filter("BYTERANGE", ap_byterange_filter,
                                  NULL, AP_FTYPE_PROTOCOL);
    ap_method_registry_init(p);
}