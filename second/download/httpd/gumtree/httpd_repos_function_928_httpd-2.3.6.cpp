void ssl_var_log_config_register(apr_pool_t *p)
{
    static APR_OPTIONAL_FN_TYPE(ap_register_log_handler) *log_pfn_register;

    log_pfn_register = APR_RETRIEVE_OPTIONAL_FN(ap_register_log_handler);

    if (log_pfn_register) {
        log_pfn_register(p, "c", ssl_var_log_handler_c, 0);
        log_pfn_register(p, "x", ssl_var_log_handler_x, 0);
    }
    return;
}