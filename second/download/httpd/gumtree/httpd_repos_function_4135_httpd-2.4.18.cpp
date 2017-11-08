static void clean_child_exit(int code)
{
    mpm_state = AP_MPMQ_STOPPING;
    if (pchild) {
        apr_pool_destroy(pchild);
    }

    if (one_process) {
        worker_note_child_killed(/* slot */ 0, 0, 0);
    }

    exit(code);
}