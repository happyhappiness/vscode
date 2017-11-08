static apr_status_t get_req(int fd, request_rec *r, char **argv0, char ***env,
                            cgid_req_t *req)
{
    int i;
    char **environ;
    core_request_config *temp_core;
    void **rconf;
    apr_status_t stat;

    r->server = apr_pcalloc(r->pool, sizeof(server_rec));

    /* read the request header */
    stat = sock_read(fd, req, sizeof(*req));
    if (stat != APR_SUCCESS) {
        return stat;
    }
    r->server->loglevel = req->loglevel;
    if (req->req_type == GETPID_REQ) {
        /* no more data sent for this request */
        return APR_SUCCESS;
    }

    /* handle module indexes and such */
    rconf = (void **) apr_pcalloc(r->pool, sizeof(void *) * (total_modules + DYNAMIC_MODULE_LIMIT));

    temp_core = (core_request_config *)apr_palloc(r->pool, sizeof(core_module));
    rconf[req->core_module_index] = (void *)temp_core;
    r->request_config = (ap_conf_vector_t *)rconf;
    ap_set_module_config(r->request_config, &cgid_module, (void *)&req->ugid);

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