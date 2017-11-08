static void signal_threads(int mode)
{
    if (terminate_mode == mode) {
        return;
    }
    terminate_mode = mode;
    mpm_state = AP_MPMQ_STOPPING;
    workers_may_exit = 1;

    worker_stack_term(idle_worker_stack);
}