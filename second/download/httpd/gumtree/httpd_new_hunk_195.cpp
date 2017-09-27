
            rc = ap_os_create_privileged_process(r, procnew, argv0, argv, 
                                                 (const char * const *)env, 
                                                 procattr, ptrans);

            if (rc != APR_SUCCESS) {
                /* Bad things happened. Everyone should have cleaned up.
                 * ap_log_rerror() won't work because the header table used by
                 * ap_log_rerror() hasn't been replicated in the phony r
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                             "couldn't create child process: %d: %s", rc, 
                             apr_filename_of_pathname(r->filename));
            }
            else {
                /* We don't want to leak storage for the key, so only allocate
                 * a key if the key doesn't exist yet in the hash; there are
                 * only a limited number of possible keys (one for each
                 * possible thread in the server), so we can allocate a copy
                 * of the key the first time a thread has a cgid request.
                 * Note that apr_hash_set() only uses the storage passed in
                 * for the key if it is adding the key to the hash for the
                 * first time; new key storage isn't needed for replacing the
                 * existing value of a key.
                 */
                void *key;

                if (apr_hash_get(script_hash, &cgid_req.conn_id, sizeof(cgid_req.conn_id))) {
                    key = &cgid_req.conn_id;
                }
                else {
                    key = apr_pcalloc(pcgi, sizeof(cgid_req.conn_id));
                    memcpy(key, &cgid_req.conn_id, sizeof(cgid_req.conn_id));
                }
                apr_hash_set(script_hash, key, sizeof(cgid_req.conn_id),
                             (void *)procnew->pid);
            }
        }
    } 
    return -1; 
} 

static int cgid_start(apr_pool_t *p, server_rec *main_server,
                      apr_proc_t *procnew)
{
    daemon_should_exit = 0; /* clear setting from previous generation */
    if ((daemon_pid = fork()) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "mod_cgid: Couldn't spawn cgid daemon process");
        return DECLINED;
    }
    else if (daemon_pid == 0) {
        if (pcgi == NULL) {
            apr_pool_create(&pcgi, p);
        }
        cgid_server(main_server);
        exit(-1);
    }
    procnew->pid = daemon_pid;
    procnew->err = procnew->in = procnew->out = NULL;
    apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
#if APR_HAS_OTHER_CHILD
    apr_proc_other_child_register(procnew, cgid_maint, procnew, NULL, p);
#endif
    return OK;
}

static int cgid_init(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, 
                     server_rec *main_server) 
{ 
    apr_proc_t *procnew = NULL;
    int first_time = 0;
    const char *userdata_key = "cgid_init";
    module **m;
    int ret = OK;

    root_server = main_server;
    root_pool = p;

    apr_pool_userdata_get((void **)&procnew, userdata_key, main_server->process->pool);
    if (!procnew) {
        first_time = 1;
        procnew = apr_pcalloc(main_server->process->pool, sizeof(*procnew));
        procnew->pid = -1;
        procnew->err = procnew->in = procnew->out = NULL;
        apr_pool_userdata_set((const void *)procnew, userdata_key,
                     apr_pool_cleanup_null, main_server->process->pool);
    }

    if (!first_time) {
        total_modules = 0;
        for (m = ap_preloaded_modules; *m != NULL; m++)
            total_modules++;

        ret = cgid_start(p, main_server, procnew);
        if (ret != OK ) {
            return ret;
        }
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
    return ret;
} 

static void *create_cgid_config(apr_pool_t *p, server_rec *s) 
{ 
    cgid_server_conf *c = 
    (cgid_server_conf *) apr_pcalloc(p, sizeof(cgid_server_conf)); 
