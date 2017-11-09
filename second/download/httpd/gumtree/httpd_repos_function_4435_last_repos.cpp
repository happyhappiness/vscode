static void clean_child_exit(int code)
{
    retained->mpm->mpm_state = AP_MPMQ_STOPPING;

    if (pchild) {
        apr_pool_destroy(pchild);
    }

    if (one_process) {
        prefork_note_child_killed(/* slot */ 0, 0, 0);
    }

    ap_mpm_pod_close(my_bucket->pod);
    chdir_for_gprof();
    exit(code);
}