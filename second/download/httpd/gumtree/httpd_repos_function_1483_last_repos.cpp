static void dbd_hooks(apr_pool_t *pool)
{
    ap_hook_pre_config(dbd_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(dbd_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(dbd_child_init, NULL, NULL, APR_HOOK_MIDDLE);

    APR_REGISTER_OPTIONAL_FN(ap_dbd_prepare);
    APR_REGISTER_OPTIONAL_FN(ap_dbd_open);
    APR_REGISTER_OPTIONAL_FN(ap_dbd_close);
    APR_REGISTER_OPTIONAL_FN(ap_dbd_acquire);
    APR_REGISTER_OPTIONAL_FN(ap_dbd_cacquire);

    APR_OPTIONAL_HOOK(dbd, post_connect, dbd_init_sql_init,
                      NULL, NULL, APR_HOOK_MIDDLE);

    apr_dbd_init(pool);
}