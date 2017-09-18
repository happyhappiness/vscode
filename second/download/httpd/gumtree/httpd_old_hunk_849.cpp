            kill(*sd, SIGHUP); /* send signal to daemon telling it to die */
            break;
    }
}
#endif

static int get_req(int fd, request_rec *r, char **argv0, char ***env, int *req_type) 
{ 
    int i, len, j, rc; 
    unsigned char *data; 
    char **environ; 
    core_dir_config *temp_core; 
    void **dconf; 
    module *suexec_mod = ap_find_linked_module("mod_suexec.c");

    r->server = apr_pcalloc(r->pool, sizeof(server_rec)); 

    rc = read(fd, req_type, sizeof(int));
    if (rc != sizeof(int)) {
        return 1;
    }
    rc = read(fd, &j, sizeof(int));
    if (rc != sizeof(int)) {
        return 1;
    }
    rc = read(fd, &len, sizeof(int));
    if (rc != sizeof(int)) {
        return 1;
    }

    data = apr_pcalloc(r->pool, len + 1); /* get a cleared byte for final '\0' */
    rc = read(fd, data, len); 
    if (rc != len) {
        return 1;
    }

    r->filename = ap_getword(r->pool, (const char **)&data, '\n'); 
    *argv0 = ap_getword(r->pool, (const char **)&data, '\n'); 

    r->uri = ap_getword(r->pool, (const char **)&data, '\n'); 
    
    environ = apr_pcalloc(r->pool, (j + 2) *sizeof(char *)); 
    i = 0; 
    for (i = 0; i < j; i++) { 
        environ[i] = ap_getword(r->pool, (const char **)&data, '\n'); 
    } 
    *env = environ; 
    r->args = ap_getword(r->pool, (const char **)&data, '\n'); 
  
    rc = read(fd, &i, sizeof(int)); 
    if (rc != sizeof(int)) {
        return 1;
    }
     
    /* add 1, so that if i == 0, we still malloc something. */ 

    dconf = (void **) apr_pcalloc(r->pool, sizeof(void *) * (total_modules + DYNAMIC_MODULE_LIMIT));

    temp_core = (core_dir_config *)apr_palloc(r->pool, sizeof(core_module)); 

    dconf[i] = (void *)temp_core; 

    if (suexec_mod) {
        suexec_config_t *suexec_cfg = apr_pcalloc(r->pool, sizeof(*suexec_cfg));

        rc = read(fd, &i, sizeof(int));
        if (rc != sizeof(int)) {
            return 1;
        }
        rc = read(fd, suexec_cfg, sizeof(*suexec_cfg));
        if (rc != sizeof(*suexec_cfg)) {
            return 1;
        }
        dconf[i] = (void *)suexec_cfg;
    }

    r->per_dir_config = (ap_conf_vector_t *)dconf; 
#if 0
#ifdef RLIMIT_CPU 
    read(fd, &j, sizeof(int)); 
    if (j) { 
        temp_core->limit_cpu = (struct rlimit *)apr_palloc (sizeof(struct rlimit)); 
        read(fd, temp_core->limit_cpu, sizeof(struct rlimit)); 
    } 
    else { 
        temp_core->limit_cpu = NULL; 
    } 
#endif 

#if defined (RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS) 
    read(fd, &j, sizeof(int)); 
    if (j) { 
        temp_core->limit_mem = (struct rlimit *)apr_palloc(r->pool, sizeof(struct rlimit)); 
        read(fd, temp_core->limit_mem, sizeof(struct rlimit)); 
    } 
    else { 
        temp_core->limit_mem = NULL; 
    } 
#endif 

#ifdef RLIMIT_NPROC 
    read(fd, &j, sizeof(int)); 
    if (j) { 
        temp_core->limit_nproc = (struct rlimit *)apr_palloc(r->pool, sizeof(struct rlimit)); 
        read(fd, temp_core->limit_nproc, sizeof(struct rlimit)); 
    } 
    else { 
        temp_core->limit_nproc = NULL; 
    } 
#endif 
#endif

    /* basic notes table to avoid segfaults */
    r->notes = apr_table_make(r->pool, 1);

    /* mod_userdir requires the mod_userdir_user note */
    rc = read(fd, &len, sizeof(len));
    if ((rc == sizeof(len)) && len) {
        data = apr_pcalloc(r->pool, len + 1); /* last byte is '\0' */
        rc = read(fd, data, len);
        if (rc != len) {
            return 1;
        }
        apr_table_set(r->notes,"mod_userdir_user", (const char *)data);
    }
    return 0;
} 



static void send_req(int fd, request_rec *r, char *argv0, char **env, int req_type) 
{ 
    int len, r_type = req_type; 
    int i = 0; 
    char *data; 
    module *suexec_mod = ap_find_linked_module("mod_suexec.c");

    data = apr_pstrcat(r->pool, r->filename, "\n", argv0, "\n", r->uri, "\n", 
                     NULL); 

    for (i =0; env[i]; i++) { 
        continue; 
    } 

    /* Write the request type (SSI "exec cmd" or cgi). */
    if (write(fd, &r_type, sizeof(int)) < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
                     "write to cgi daemon process");
    }

    /* Write the number of entries in the environment. */
    if (write(fd, &i, sizeof(int)) < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
                     "write to cgi daemon process"); 
        }     

    for (i = 0; env[i]; i++) { 
        data = apr_pstrcat(r->pool, data, env[i], "\n", NULL); 
    } 
    data = apr_pstrcat(r->pool, data, r->args, NULL); 
    len = strlen(data); 
    /* Write the length of the concatenated env string. */
    if (write(fd, &len, sizeof(int)) < 0) { 
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
                     "write to cgi daemon process"); 
    }
    /* Write the concatted env string. */     
    if (write(fd, data, len) < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
                     "write to cgi daemon process"); 
    }
    /* Write module_index id value. */     
    if (write(fd, &core_module.module_index, sizeof(int)) < 0) { 
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
                     "write to cgi daemon process"); 
    }     
    if (suexec_mod) {
        suexec_config_t *suexec_cfg = ap_get_module_config(r->per_dir_config,
                                                           suexec_mod);

        write(fd, &suexec_mod->module_index, sizeof(int));
        write(fd, suexec_cfg, sizeof(*suexec_cfg));
    }

#if 0
#ifdef RLIMIT_CPU 
    if (conf->limit_cpu) { 
        len = 1; 
        write(fd, &len, sizeof(int)); 
        write(fd, conf->limit_cpu, sizeof(struct rlimit)); 
    } 
    else { 
        len = 0; 
        write(fd, &len, sizeof(int)); 
    } 
#endif 

#if defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS) 
    if (conf->limit_mem) { 
        len = 1; 
        write(fd, &len, sizeof(int)); 
        write(fd, conf->limit_mem, sizeof(struct rlimit)); 
    } 
    else { 
        len = 0; 
        write(fd, &len, sizeof(int)); 
    } 
#endif 
  
#ifdef RLIMIT_NPROC 
    if (conf->limit_nproc) { 
        len = 1; 
        write(fd, &len, sizeof(int)); 
        write(fd, conf->limit_nproc, sizeof(struct rlimit)); 
    } 
    else { 
        len = 0; 
        write(fd, &len, sizeof(int)); 
    } 
#endif
#endif 
   /* send a minimal notes table */
   data  = (char *) apr_table_get(r->notes, "mod_userdir_user");
   if (data != NULL) {
       len = strlen(data);
       write(fd, &len, sizeof(len));
       write(fd, data, len);
   }
   else {
       len = 0;
       write(fd, &len, sizeof(len));
   }
} 

static void daemon_signal_handler(int sig)
{
    if (sig == SIGHUP) {
        ++daemon_should_exit;
    }
}

static int cgid_server(void *data) 
{ 
    struct sockaddr_un unix_addr;
    int sd, sd2, rc, req_type;
    mode_t omask;
    apr_socklen_t len;
    apr_pool_t *ptrans;
    server_rec *main_server = data;
    cgid_server_conf *sconf = ap_get_module_config(main_server->module_config,
                                                   &cgid_module); 

    apr_pool_create(&ptrans, pcgi); 

    apr_signal(SIGCHLD, SIG_IGN); 
    apr_signal(SIGHUP, daemon_signal_handler);

