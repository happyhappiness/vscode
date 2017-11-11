static void register_hooks(apr_pool_t *p)
{
    ap_register_provider(p, "dav-lock", "generic", "0",
                         &dav_hooks_locks_generic);
}