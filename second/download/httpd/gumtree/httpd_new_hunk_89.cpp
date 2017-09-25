            continue;
        }
       
        r = apr_pcalloc(ptrans, sizeof(request_rec)); 
        procnew = apr_pcalloc(ptrans, sizeof(*procnew));
        r->pool = ptrans; 
        stat = get_req(sd2, r, &argv0, &env, &cgid_req); 
        if (stat != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, stat,
                         main_server,
                         "Error reading request on cgid socket");
            close(sd2);
            continue;
        }

        if (cgid_req.req_type == GETPID_REQ) {
            pid_t pid;

            pid = (pid_t)apr_hash_get(script_hash, &cgid_req.conn_id, sizeof(cgid_req.conn_id));
            if (write(sd2, &pid, sizeof(pid)) != sizeof(pid)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             main_server,
                             "Error writing pid %" APR_PID_T_FMT " to handler", pid);
            }
            close(sd2);
            continue;
        }

        apr_os_file_put(&r->server->error_log, &errfileno, 0, r->pool);
        apr_os_file_put(&inout, &sd2, 0, r->pool);

        if (cgid_req.req_type == SSI_REQ) {
            in_pipe  = APR_NO_PIPE;
            out_pipe = APR_FULL_BLOCK;
            err_pipe = APR_NO_PIPE;
            cmd_type = APR_SHELLCMD;
        }
        else {
