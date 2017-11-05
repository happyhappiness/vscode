static int simple_run(apr_pool_t * pconf, apr_pool_t * plog, server_rec * s)
{
    simple_core_t *sc = simple_core_get();

    sc->mpm_state = AP_MPMQ_RUNNING;

    if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
        sc->mpm_state = AP_MPMQ_STOPPING;
        return DONE;
    }

    return simple_main_loop(sc);
}