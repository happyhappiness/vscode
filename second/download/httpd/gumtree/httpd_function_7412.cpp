static apr_status_t podx_signal_internal(ap_pod_t *pod,
                                        ap_podx_restart_t graceful)
{
    apr_status_t rv;
    apr_size_t one = 1;
    char char_of_death = ' ';
    switch (graceful) {
        case AP_MPM_PODX_RESTART:
            char_of_death = AP_MPM_PODX_RESTART_CHAR;
            break;
        case AP_MPM_PODX_GRACEFUL:
            char_of_death = AP_MPM_PODX_GRACEFUL_CHAR;
            break;
        case AP_MPM_PODX_NORESTART:
            break;
    }

    rv = apr_file_write(pod->pod_out, &char_of_death, &one);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf, APLOGNO(2404)
                     "write pipe_of_death");
    }
    return rv;
}