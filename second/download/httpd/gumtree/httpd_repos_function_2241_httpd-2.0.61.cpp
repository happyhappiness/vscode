static int perchild_open_logs(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;

    pconf = p;
    ap_server_conf = s;

    if ((num_listensocks = ap_setup_listeners(ap_server_conf)) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0,
                     NULL, "no listening sockets available, shutting down");
        return DONE;
    }

    ap_log_pid(pconf, ap_pid_fname);

    if ((rv = ap_mpm_pod_open(pconf, &pod))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT|APLOG_STARTUP, rv, NULL,
                "Could not open pipe-of-death.");
        return DONE;
    }

    if ((rv = apr_file_pipe_create(&pipe_of_death_in, &pipe_of_death_out,
                                   pconf)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv,
                     (const server_rec*) ap_server_conf,
                     "apr_file_pipe_create (pipe_of_death)");
        exit(1);
    }
    if ((rv = apr_file_pipe_timeout_set(pipe_of_death_in, 0)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv,
                     (const server_rec*) ap_server_conf,
                     "apr_file_pipe_timeout_set (pipe_of_death)");
        exit(1);
    }

    return OK;
}