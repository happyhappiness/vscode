static apr_status_t pod_signal_internal(ap_pod_t *pod, int graceful)
{
    apr_status_t rv;
    char char_of_death = graceful ? GRACEFUL_CHAR : RESTART_CHAR;
    apr_size_t one = 1;

    rv = apr_file_write(pod->pod_out, &char_of_death, &one);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                     "write pipe_of_death");
    }
    return rv;
}
