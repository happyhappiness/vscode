static void exipc_register_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(exipc_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(exipc_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(exipc_child_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(exipc_handler, NULL, NULL, APR_HOOK_MIDDLE);
}