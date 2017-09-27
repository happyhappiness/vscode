    ap_extended_status = 0;
    ap_min_spare_threads = DEFAULT_MIN_SPARE_THREAD;
    ap_max_spare_threads = DEFAULT_MAX_SPARE_THREAD;
#ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
        ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
#endif

    return OK;
}



static void mpmt_os2_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(mpmt_os2_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}



static const char *set_daemons_to_start(cmd_parms *cmd, void *dummy, const char *arg)
{
