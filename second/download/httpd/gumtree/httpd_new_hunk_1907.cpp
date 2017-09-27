                           " is not a directory", NULL);
    }
    apr_cpystrn(ap_coredump_dir, fname, sizeof(ap_coredump_dir));
    ap_coredumpdir_configured = 1;
    return NULL;
}

int ap_graceful_shutdown_timeout = 0;

const char * ap_mpm_set_graceful_shutdown(cmd_parms *cmd, void *dummy,
                                          const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }
    ap_graceful_shutdown_timeout = atoi(arg);
    return NULL;
}

apr_uint32_t ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;

const char *ap_mpm_set_max_mem_free(cmd_parms *cmd, void *dummy,
                                    const char *arg)
{
    long value;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    value = strtol(arg, NULL, 0);
    if (value < 0 || errno == ERANGE)
        return apr_pstrcat(cmd->pool, "Invalid MaxMemFree value: ",
                           arg, NULL);

    ap_max_mem_free = (apr_uint32_t)value * 1024;

    return NULL;
}

apr_size_t ap_thread_stacksize = 0; /* use system default */

const char *ap_mpm_set_thread_stacksize(cmd_parms *cmd, void *dummy,
                                        const char *arg)
{
    long value;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    value = strtol(arg, NULL, 0);
    if (value < 0 || errno == ERANGE)
        return apr_pstrcat(cmd->pool, "Invalid ThreadStackSize value: ",
                           arg, NULL);

    ap_thread_stacksize = (apr_size_t)value;

    return NULL;
}

AP_DECLARE(apr_status_t) ap_mpm_query(int query_code, int *result)
{
    apr_status_t rv;

    if (ap_run_mpm_query(query_code, result, &rv) == DECLINED) {
        rv = APR_EGENERAL;
    }

    return rv;
}

AP_DECLARE(apr_status_t) ap_mpm_note_child_killed(int childnum)
{
    return ap_run_mpm_note_child_killed(childnum);
}

AP_DECLARE(apr_status_t) ap_mpm_register_timed_callback(apr_time_t t, ap_mpm_callback_fn_t *cbfn, void *baton)
{
    return ap_run_mpm_register_timed_callback(t, cbfn, baton);
}

AP_DECLARE(const char *)ap_show_mpm(void)
{
    const char *name = ap_run_mpm_get_name();

    if (!name) {
        name = "";
    }

    return name;
}
