    ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
#endif

    return OK;
}

static void netware_mpm_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(netware_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}

void netware_rewrite_args(process_rec *process)
{
    char *def_server_root;
    char optbuf[3];
