static void clean_child_exit(int code)
{
    mpm_state = AP_MPMQ_STOPPING;

    if (pchild) {
        apr_pool_destroy(pchild);
    }
    ap_mpm_pod_close(pod);
    chdir_for_gprof();
    exit(code);
}