static void suexec_hooks(apr_pool_t *p)
{
    ap_hook_get_suexec_identity(get_suexec_id_doer,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_post_config(suexec_post_config,NULL,NULL,APR_HOOK_MIDDLE);
}