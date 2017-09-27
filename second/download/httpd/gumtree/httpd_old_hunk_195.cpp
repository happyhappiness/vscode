
            rc = ap_os_create_privileged_process(r, procnew, argv0, argv, 
                                                 (const char * const *)env, 
                                                 procattr, ptrans);

            if (rc != APR_SUCCESS) {
                /* Bad things happened. Everyone should have cleaned up. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, rc, r,
                              "couldn't create child process: %d: %s", rc, 
                              apr_filename_of_pathname(r->filename));
            }
            else {
                apr_hash_set(script_hash, &cgid_req.conn_id, sizeof(cgid_req.conn_id), 
                             (void *)procnew->pid);
            }
        }
    } 
    return -1; 
} 

static int cgid_init(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, 
                      server_rec *main_server) 
{ 
    apr_proc_t *procnew;
    void *data;
    int first_time = 0;
    const char *userdata_key = "cgid_init";
    module **m;

    apr_pool_userdata_get(&data, userdata_key, main_server->process->pool);
    if (!data) {
        first_time = 1;
        apr_pool_userdata_set((const void *)1, userdata_key,
                         apr_pool_cleanup_null, main_server->process->pool);
    }

    if (!first_time) {
        total_modules = 0;
        for (m = ap_preloaded_modules; *m != NULL; m++)
            total_modules++;

        daemon_should_exit = 0; /* clear setting from previous generation */
        if ((daemon_pid = fork()) < 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server, 
                         "mod_cgid: Couldn't spawn cgid daemon process"); 
            return DECLINED;
        }
        else if (daemon_pid == 0) {
            apr_pool_create(&pcgi, p); 
            cgid_server(main_server);
            exit(-1);
        } 
        procnew = apr_pcalloc(p, sizeof(*procnew));
        procnew->pid = daemon_pid;
        procnew->err = procnew->in = procnew->out = NULL;
        apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
#if APR_HAS_OTHER_CHILD
        apr_proc_other_child_register(procnew, cgid_maint, &procnew->pid, NULL, p);
#endif

        cgid_pfn_reg_with_ssi = APR_RETRIEVE_OPTIONAL_FN(ap_register_include_handler);
        cgid_pfn_gtv          = APR_RETRIEVE_OPTIONAL_FN(ap_ssi_get_tag_and_value);
        cgid_pfn_ps           = APR_RETRIEVE_OPTIONAL_FN(ap_ssi_parse_string);

        if ((cgid_pfn_reg_with_ssi) && (cgid_pfn_gtv) && (cgid_pfn_ps)) {
            /* Required by mod_include filter. This is how mod_cgid registers
             *   with mod_include to provide processing of the exec directive.
             */
            cgid_pfn_reg_with_ssi("exec", handle_exec);
        }
    }
    return OK;
} 

static void *create_cgid_config(apr_pool_t *p, server_rec *s) 
{ 
    cgid_server_conf *c = 
    (cgid_server_conf *) apr_pcalloc(p, sizeof(cgid_server_conf)); 
