}

/**************************************************************** 
 * 
 * Actual cgid handling... 
 */ 

struct cleanup_script_info {
    request_rec *r;
    unsigned long conn_id;
    cgid_server_conf *conf;
};

static apr_status_t dead_yet(pid_t pid, apr_interval_time_t max_wait)
{
    apr_interval_time_t interval = 10000; /* 10 ms */
    apr_interval_time_t total = 0;

    do {
        if (kill(pid, 0) < 0) {
            return APR_SUCCESS;
        }
        apr_sleep(interval);
        total = total + interval;
        if (interval < 500000) {
            interval *= 2;
        }
    } while (total < max_wait);
    return APR_EGENERAL;
}

static apr_status_t cleanup_nonchild_process(request_rec *r, pid_t pid)
{
    kill(pid, SIGTERM); /* in case it isn't dead yet */
    if (dead_yet(pid, apr_time_from_sec(3)) == APR_SUCCESS) {
        return APR_SUCCESS;
    }
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "CGI process %" APR_PID_T_FMT " didn't exit, sending SIGKILL",
                  pid);
    kill(pid, SIGKILL);
    if (dead_yet(pid, apr_time_from_sec(3)) == APR_SUCCESS) {
        return APR_SUCCESS;
    }
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "CGI process %" APR_PID_T_FMT " didn't exit, sending SIGKILL again",
                  pid);
    kill(pid, SIGKILL);

    return APR_EGENERAL;
}

static apr_status_t cleanup_script(void *vptr)
{
    struct cleanup_script_info *info = vptr;
    int sd;
    int rc;
    cgid_req_t req = {0};
    pid_t pid;
    apr_status_t stat;

    rc = connect_to_daemon(&sd, info->r, info->conf);
    if (rc != OK) {
        return APR_EGENERAL;
    }

    req.req_type = GETPID_REQ;
    req.conn_id = info->r->connection->id;

    stat = sock_write(sd, &req, sizeof(req));
    if (stat != APR_SUCCESS) {
        close(sd);
        return stat;
    }

    /* wait for pid of script */
    stat = sock_read(sd, &pid, sizeof(pid));
    if (stat != APR_SUCCESS) {
        close(sd);
        return stat;
    }
    close(sd);

    if (pid == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, info->r,
                      "daemon couldn't find CGI process for connection %lu",
                      info->conn_id);
        return APR_EGENERAL;
    }
    return cleanup_nonchild_process(info->r, pid);
}

static int cgid_handler(request_rec *r) 
{ 
    conn_rec *c = r->connection;
    int retval, nph, dbpos = 0; 
    char *argv0, *dbuf = NULL; 
    apr_bucket_brigade *bb;
