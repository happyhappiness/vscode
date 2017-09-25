            kill(*sd, SIGHUP); /* send signal to daemon telling it to die */
            break;
    }
}
#endif

/* deal with incomplete reads and signals
 * assume you really have to read buf_size bytes
 */
static apr_status_t sock_read(int fd, void *vbuf, size_t buf_size)
{
    char *buf = vbuf;
    int rc;
    size_t bytes_read = 0;

    do {
        do {
            rc = read(fd, buf + bytes_read, buf_size - bytes_read);
        } while (rc < 0 && errno == EINTR);
        switch(rc) {
        case -1:
            return errno;
        case 0: /* unexpected */
            return ECONNRESET;
        default:
            bytes_read += rc;
        }
    } while (bytes_read < buf_size);

    return APR_SUCCESS;
}

/* deal with signals
 */
static apr_status_t sock_write(int fd, const void *buf, size_t buf_size)
{
    int rc;

    do {
        rc = write(fd, buf, buf_size);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        return errno;
    }

    return APR_SUCCESS;
}

static apr_status_t get_req(int fd, request_rec *r, char **argv0, char ***env, 
                            cgid_req_t *req)
{ 
    int i; 
    char *user;
    char **environ; 
    core_dir_config *temp_core; 
    void **dconf;
    apr_status_t stat;

    r->server = apr_pcalloc(r->pool, sizeof(server_rec)); 

    /* read the request header */
    stat = sock_read(fd, req, sizeof(*req));
    if (stat != APR_SUCCESS) {
        return stat;
    }
    if (req->req_type == GETPID_REQ) {
        /* no more data sent for this request */
        return APR_SUCCESS;
    }

    /* handle module indexes and such */
    dconf = (void **) apr_pcalloc(r->pool, sizeof(void *) * (total_modules + DYNAMIC_MODULE_LIMIT));

    temp_core = (core_dir_config *)apr_palloc(r->pool, sizeof(core_module)); 
    dconf[req->core_module_index] = (void *)temp_core;

    if (req->have_suexec) {
        dconf[req->suexec_module_index] = &req->suexec_cfg;
    }

    r->per_dir_config = (ap_conf_vector_t *)dconf; 

    /* Read the filename, argv0, uri, and args */
    r->filename = apr_pcalloc(r->pool, req->filename_len + 1);
    *argv0 = apr_pcalloc(r->pool, req->argv0_len + 1);
    r->uri = apr_pcalloc(r->pool, req->uri_len + 1);
    if ((stat = sock_read(fd, r->filename, req->filename_len)) != APR_SUCCESS ||
        (stat = sock_read(fd, *argv0, req->argv0_len)) != APR_SUCCESS ||
        (stat = sock_read(fd, r->uri, req->uri_len)) != APR_SUCCESS) {
        return stat;
    }

    r->args = apr_pcalloc(r->pool, req->args_len + 1); /* empty string if no args */
    if (req->args_len) {
        if ((stat = sock_read(fd, r->args, req->args_len)) != APR_SUCCESS) {
            return stat;
        }
    }

    /* read the environment variables */
    environ = apr_pcalloc(r->pool, (req->env_count + 2) *sizeof(char *));
    for (i = 0; i < req->env_count; i++) {
        apr_size_t curlen;

        if ((stat = sock_read(fd, &curlen, sizeof(curlen))) != APR_SUCCESS) {
            return stat;
        }
        environ[i] = apr_pcalloc(r->pool, curlen + 1);
        if ((stat = sock_read(fd, environ[i], curlen)) != APR_SUCCESS) {
            return stat;
        }
    }
    *env = environ;

    /* basic notes table to avoid segfaults */
    r->notes = apr_table_make(r->pool, 1);

    /* mod_userdir requires the mod_userdir_user note */
    if (req->mod_userdir_user_len) {
        user = apr_pcalloc(r->pool, req->mod_userdir_user_len + 1); /* last byte is '\0' */
        stat = sock_read(fd, user, req->mod_userdir_user_len);
        if (stat != APR_SUCCESS) {
            return stat;
        }
        apr_table_set(r->notes, "mod_userdir_user", (const char *)user);
    }

#if 0
#ifdef RLIMIT_CPU 
    sock_read(fd, &j, sizeof(int)); 
    if (j) { 
        temp_core->limit_cpu = (struct rlimit *)apr_palloc (sizeof(struct rlimit)); 
        sock_read(fd, temp_core->limit_cpu, sizeof(struct rlimit)); 
    } 
    else { 
        temp_core->limit_cpu = NULL; 
    } 
#endif 

#if defined (RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS) 
    sock_read(fd, &j, sizeof(int)); 
    if (j) { 
        temp_core->limit_mem = (struct rlimit *)apr_palloc(r->pool, sizeof(struct rlimit)); 
        sock_read(fd, temp_core->limit_mem, sizeof(struct rlimit)); 
    } 
    else { 
        temp_core->limit_mem = NULL; 
    } 
#endif 

#ifdef RLIMIT_NPROC 
    sock_read(fd, &j, sizeof(int)); 
    if (j) { 
        temp_core->limit_nproc = (struct rlimit *)apr_palloc(r->pool, sizeof(struct rlimit)); 
        sock_read(fd, temp_core->limit_nproc, sizeof(struct rlimit)); 
    } 
    else { 
        temp_core->limit_nproc = NULL; 
    } 
#endif 
#endif

    return APR_SUCCESS;
} 

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

static void daemon_signal_handler(int sig)
{
    if (sig == SIGHUP) {
        ++daemon_should_exit;
    }
}

static int cgid_server(void *data) 
{ 
    struct sockaddr_un unix_addr;
    int sd, sd2, rc;
    mode_t omask;
    apr_socklen_t len;
    apr_pool_t *ptrans;
    server_rec *main_server = data;
    cgid_server_conf *sconf = ap_get_module_config(main_server->module_config,
                                                   &cgid_module); 
    apr_hash_t *script_hash = apr_hash_make(pcgi);

    apr_pool_create(&ptrans, pcgi); 

    apr_signal(SIGCHLD, SIG_IGN); 
    apr_signal(SIGHUP, daemon_signal_handler);

