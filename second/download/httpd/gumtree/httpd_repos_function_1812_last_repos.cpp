static apr_status_t get_cgi_pid(request_rec *r,  cgid_server_conf *conf, pid_t *pid) { 
    cgid_req_t req = {0};
    apr_status_t stat;
    int rc, sd;

    rc = connect_to_daemon(&sd, r, conf);
    if (rc != OK) {
        return APR_EGENERAL;
    }

    req.req_type = GETPID_REQ;
    req.ppid = parent_pid;
    req.conn_id = r->connection->id;

    stat = sock_write(sd, &req, sizeof(req));
    if (stat != APR_SUCCESS) {
        return stat;
    }

    /* wait for pid of script */
    stat = sock_read(sd, pid, sizeof(*pid));
    if (stat != APR_SUCCESS) {
        return stat;
    }

    if (pid == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01261)
                      "daemon couldn't find CGI process for connection %lu",
                      r->connection->id);
        return APR_EGENERAL;
    }

    return APR_SUCCESS;
}