       
        r = apr_pcalloc(ptrans, sizeof(request_rec)); 
        procnew = apr_pcalloc(ptrans, sizeof(*procnew));
        r->pool = ptrans; 
        rc = get_req(sd2, r, &argv0, &env, &req_type); 
        if (rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0,
                         main_server,
                         "Error reading request on cgid socket");
            close(sd2);
            continue;
        }
        apr_os_file_put(&r->server->error_log, &errfileno, 0, r->pool);
