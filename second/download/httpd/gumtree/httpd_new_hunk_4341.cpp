    request_rec *r = f->r;
    cgid_server_conf *conf = ap_get_module_config(r->server->module_config,
                                                  &cgid_module);
    cgid_dirconf *dc = ap_get_module_config(r->per_dir_config, &cgid_module);

    struct cleanup_script_info *info;
    apr_status_t rv;

    add_ssi_vars(r);
    env = ap_create_environment(r->pool, r->subprocess_env);

    if ((retval = connect_to_daemon(&sd, r, conf)) != OK) {
        return retval;
    }

    send_req(sd, r, command, env, SSI_REQ);

    info = apr_palloc(r->pool, sizeof(struct cleanup_script_info));
    info->conf = conf;
    info->r = r;
    rv = get_cgi_pid(r, conf, &(info->pid));
    if (APR_SUCCESS == rv) {             
        /* for this type of request, the script is invoked through an
         * intermediate shell process...  cleanup_script is only able
         * to knock out the shell process, not the actual script
         */
        apr_pool_cleanup_register(r->pool, info,
                                  cleanup_script,
                                  apr_pool_cleanup_null);
    }
    else { 
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, "error determining cgi PID (for SSI)");
    }

    apr_pool_cleanup_register(r->pool, info,
                              cleanup_script,
                              apr_pool_cleanup_null);

    /* We are putting the socket discriptor into an apr_file_t so that we can
     * use a pipe bucket to send the data to the client.  APR will create
