static void hm_register_hooks(apr_pool_t *p)
{
    static const char * const aszSucc[]={ "mod_proxy.c", NULL };
    ap_hook_post_config(hm_post_config, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_handler(hm_handler, NULL, aszSucc, APR_HOOK_FIRST);
}