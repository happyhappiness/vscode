static apr_status_t cleanup_nonchild_process(request_rec *r, pid_t pid)
{
    kill(pid, SIGTERM); /* in case it isn't dead yet */
    if (dead_yet(pid, apr_time_from_sec(3)) == APR_SUCCESS) {
        return APR_SUCCESS;
    }
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01259)
                  "CGI process %" APR_PID_T_FMT " didn't exit, sending SIGKILL",
                  pid);
    kill(pid, SIGKILL);
    if (dead_yet(pid, apr_time_from_sec(3)) == APR_SUCCESS) {
        return APR_SUCCESS;
    }
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01260)
                  "CGI process %" APR_PID_T_FMT " didn't exit, sending SIGKILL again",
                  pid);
    kill(pid, SIGKILL);

    return APR_EGENERAL;
}
