
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
