    if ((retval = connect_to_daemon(&sd, r, conf)) != OK) {
        return retval;
    }

    rv = send_req(sd, r, argv0, env, CGI_REQ);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01268)
                     "write to cgi daemon process");
    }

    info = apr_palloc(r->pool, sizeof(struct cleanup_script_info));
    info->r = r;
    info->conn_id = r->connection->id;
