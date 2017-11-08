static apr_status_t send_req(int fd, request_rec *r, char *argv0, char **env, 
                             int req_type) 
{ 
    int i;
    const char *user;
    module *suexec_mod = ap_find_linked_module("mod_suexec.c");
    cgid_req_t req = {0};
    suexec_config_t *suexec_cfg;
    apr_status_t stat;

    req.req_type = req_type;
    req.conn_id = r->connection->id;
    req.core_module_index = core_module.module_index;
    if (suexec_mod) {
        req.have_suexec = 1;
        req.suexec_module_index = suexec_mod->module_index;
        suexec_cfg = ap_get_module_config(r->per_dir_config,
                                          suexec_mod);
        req.suexec_cfg = *suexec_cfg;
    }
    for (req.env_count = 0; env[req.env_count]; req.env_count++) {
        continue; 
    }
    req.filename_len = strlen(r->filename);
    req.argv0_len = strlen(argv0);
    req.uri_len = strlen(r->uri);
    req.args_len = r->args ? strlen(r->args) : 0;
    user = (const char *)apr_table_get(r->notes, "mod_userdir_user");
    if (user != NULL) {
        req.mod_userdir_user_len = strlen(user);
    }

    /* Write the request header */
    if ((stat = sock_write(fd, &req, sizeof(req))) != APR_SUCCESS) {
        return stat;
    }

    /* Write filename, argv0, uri, and args */
    if ((stat = sock_write(fd, r->filename, req.filename_len)) != APR_SUCCESS ||
        (stat = sock_write(fd, argv0, req.argv0_len)) != APR_SUCCESS ||
        (stat = sock_write(fd, r->uri, req.uri_len)) != APR_SUCCESS) {
        return stat;
    }
    if (req.args_len) {
        if ((stat = sock_write(fd, r->args, req.args_len)) != APR_SUCCESS) {
            return stat;
        }
    }

    /* write the environment variables */
    for (i = 0; i < req.env_count; i++) {
        apr_size_t curlen = strlen(env[i]);

        if ((stat = sock_write(fd, &curlen, sizeof(curlen))) != APR_SUCCESS) {
            return stat;
        }
            
        if ((stat = sock_write(fd, env[i], curlen)) != APR_SUCCESS) {
            return stat;
        }
    }

    /* send a minimal notes table */
    if (user) {
        if ((stat = sock_write(fd, user, req.mod_userdir_user_len)) != APR_SUCCESS) {
            return stat;
        }
    }

#if 0
#ifdef RLIMIT_CPU 
    if (conf->limit_cpu) { 
        len = 1; 
        stat = sock_write(fd, &len, sizeof(int)); 
        stat = sock_write(fd, conf->limit_cpu, sizeof(struct rlimit)); 
    } 
    else { 
        len = 0; 
        stat = sock_write(fd, &len, sizeof(int)); 
    } 
#endif 

#if defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS) 
    if (conf->limit_mem) { 
        len = 1; 
        stat = sock_write(fd, &len, sizeof(int)); 
        stat = sock_write(fd, conf->limit_mem, sizeof(struct rlimit)); 
    } 
    else { 
        len = 0; 
        stat = sock_write(fd, &len, sizeof(int)); 
    } 
#endif 
  
#ifdef RLIMIT_NPROC 
    if (conf->limit_nproc) { 
        len = 1; 
        stat = sock_write(fd, &len, sizeof(int)); 
        stat = sock_write(fd, conf->limit_nproc, sizeof(struct rlimit)); 
    } 
    else { 
        len = 0; 
        stat = sock_write(fd, &len, sizeof(int)); 
    } 
#endif
#endif
    return APR_SUCCESS;
}