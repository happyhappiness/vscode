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
