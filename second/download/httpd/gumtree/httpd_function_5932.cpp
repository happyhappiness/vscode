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

    /* we got a socket, and there is already a cleanup registered for it */

    req.req_type = GETPID_REQ;
    req.ppid = parent_pid;
    req.conn_id = info->r->connection->id;

    stat = sock_write(sd, &req, sizeof(req));
    if (stat != APR_SUCCESS) {
        return stat;
    }

    /* wait for pid of script */
    stat = sock_read(sd, &pid, sizeof(pid));
    if (stat != APR_SUCCESS) {
        return stat;
    }

    if (pid == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, info->r, APLOGNO(01261)
                      "daemon couldn't find CGI process for connection %lu",
                      info->conn_id);
        return APR_EGENERAL;
    }
    return cleanup_nonchild_process(info->r, pid);
}