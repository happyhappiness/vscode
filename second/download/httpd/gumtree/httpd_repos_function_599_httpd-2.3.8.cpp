static void register_hooks(apr_pool_t *p)
{
    ap_hook_post_config(unique_id_global_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(unique_id_child_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_read_request(gen_unique_id, NULL, NULL, APR_HOOK_MIDDLE);
}