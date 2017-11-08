apr_status_t ap_mpm_end_gen_helper(void *unused) /* cleanup on pconf */
{
    int gen = ap_config_generation - 1; /* differs from MPM generation */
    mpm_gen_info_t *cur;

    if (geninfo == NULL) {
        /* initial pconf teardown, MPM hasn't run */
        return APR_SUCCESS;
    }

    cur = APR_RING_FIRST(geninfo);
    while (cur != APR_RING_SENTINEL(geninfo, mpm_gen_info_t, link) &&
           cur->gen != gen) {
        cur = APR_RING_NEXT(cur, link);
    }

    if (cur == APR_RING_SENTINEL(geninfo, mpm_gen_info_t, link)) {
        /* last child of generation already exited */
        ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, ap_server_conf,
                     "no record of generation %d", gen);
    }
    else {
        cur->done = 1;
        if (cur->active == 0) {
            end_gen(cur);
        }
    }

    return APR_SUCCESS;
}