static void register_hooks(apr_pool_t *p)
{
    ap_hook_log_transaction(log_debug_log_transaction, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_quick_handler(log_debug_quick_handler, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_handler(log_debug_handler, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_translate_name(log_debug_translate_name, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_map_to_storage(log_debug_map_to_storage, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_fixups(log_debug_fixups, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_type_checker(log_debug_type_checker, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_check_access(log_debug_check_access, NULL, NULL, APR_HOOK_FIRST, AP_AUTH_INTERNAL_PER_URI);
    ap_hook_check_access_ex(log_debug_check_access_ex, NULL, NULL, APR_HOOK_FIRST, AP_AUTH_INTERNAL_PER_URI);
    ap_hook_check_authn(log_debug_check_authn, NULL, NULL, APR_HOOK_FIRST, AP_AUTH_INTERNAL_PER_URI);
    ap_hook_check_authz(log_debug_check_authz, NULL, NULL, APR_HOOK_FIRST, AP_AUTH_INTERNAL_PER_URI);
    ap_hook_insert_filter(log_debug_insert_filter, NULL, NULL, APR_HOOK_FIRST);
}