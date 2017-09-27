        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                     "write pipe_of_death");
    }
    return rv;
}

AP_DECLARE(apr_status_t) ap_mpm_pod_signal(ap_pod_t *pod, int graceful)
{
    return pod_signal_internal(pod, graceful);
}

AP_DECLARE(void) ap_mpm_pod_killpg(ap_pod_t *pod, int num, int graceful)
{
    int i;
    apr_status_t rv = APR_SUCCESS;

    for (i = 0; i < num && rv == APR_SUCCESS; i++) {
        rv = pod_signal_internal(pod, graceful);
