            continue;
        }
       
        r = apr_pcalloc(ptrans, sizeof(request_rec)); 
        procnew = apr_pcalloc(ptrans, sizeof(*procnew));
        r->pool = ptrans; 
        rc = get_req(sd2, r, &argv0, &env, &req_type); 
        if (rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                         main_server,
                         "Error reading request on cgid socket");
            close(sd2);
            continue;
        }
        apr_os_file_put(&r->server->error_log, &errfileno, 0, r->pool);
        apr_os_file_put(&inout, &sd2, 0, r->pool);

        if (req_type == SSI_REQ) {
            in_pipe  = APR_NO_PIPE;
            out_pipe = APR_FULL_BLOCK;
            err_pipe = APR_NO_PIPE;
            cmd_type = APR_SHELLCMD;
        }
        else {
