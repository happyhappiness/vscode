static void register_hooks(apr_pool_t *p)
{
    ap_hook_process_connection(process_echo_connection, NULL, NULL,
                               APR_HOOK_MIDDLE);
}