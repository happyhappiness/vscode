static void x_register_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(x_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_config(x_check_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_test_config(x_test_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_open_logs(x_open_logs, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(x_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(x_child_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(x_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_quick_handler(x_quick_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_connection(x_pre_connection, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_process_connection(x_process_connection, NULL, NULL, APR_HOOK_MIDDLE);
    /* [1] post read_request handling */
    ap_hook_post_read_request(x_post_read_request, NULL, NULL,
                              APR_HOOK_MIDDLE);
    ap_hook_log_transaction(x_log_transaction, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_http_scheme(x_http_scheme, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_default_port(x_default_port, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_translate_name(x_translate_name, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_map_to_storage(x_map_to_storage, NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_header_parser(x_header_parser, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_fixups(x_fixups, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_type_checker(x_type_checker, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_access(x_check_access, NULL, NULL, APR_HOOK_MIDDLE,
                         AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_check_authn(x_check_authn, NULL, NULL, APR_HOOK_MIDDLE,
                        AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_check_authz(x_check_authz, NULL, NULL, APR_HOOK_MIDDLE,
                        AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_insert_filter(x_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_insert_error_filter(x_insert_error_filter, NULL, NULL, APR_HOOK_MIDDLE);
#ifdef HAVE_UNIX_SUEXEC
    ap_hook_get_suexec_identity(x_get_suexec_identity, NULL, NULL, APR_HOOK_MIDDLE);
#endif
    ap_hook_create_connection(x_create_connection, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_get_mgmt_items(x_get_mgmt_items, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_create_request(x_create_request, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_mpm(x_pre_mpm, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_monitor(x_monitor, NULL, NULL, APR_HOOK_MIDDLE); 
}