static void register_hooks(apr_pool_t *p)
{
#ifndef NO_DLOPEN
    APR_REGISTER_OPTIONAL_FN(ap_find_loaded_module_symbol);
    ap_hook_test_config(dump_loaded_modules, NULL, NULL, APR_HOOK_MIDDLE);
#endif
}