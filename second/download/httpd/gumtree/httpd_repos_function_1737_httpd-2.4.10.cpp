static apr_status_t send_req(int fd, request_rec *r, char *argv0, char **env,
                             int req_type)
{
    int i;
    cgid_req_t req = {0};
    apr_status_t stat;
    ap_unix_identity_t * ugid = ap_run_get_suexec_identity(r);
    core_dir_config *core_conf = ap_get_core_module_config(r->per_dir_config);


    if (ugid == NULL) {
        req.ugid = empty_ugid;
    } else {
        memcpy(&req.ugid, ugid, sizeof(ap_unix_identity_t));
    }

    req.req_type = req_type;
    req.ppid = parent_pid;
    req.conn_id = r->connection->id;
    for (req.env_count = 0; env[req.env_count]; req.env_count++) {
        continue;
    }
    req.filename_len = strlen(r->filename);
    req.argv0_len = strlen(argv0);
    req.uri_len = strlen(r->uri);
    req.args_len = r->args ? strlen(r->args) : 0;
    req.loglevel = r->server->log.level;

    /* Write the request header */
    if (req.args_len) {
        stat = sock_writev(fd, r, 5,
                           &req, sizeof(req),
                           r->filename, req.filename_len,
                           argv0, req.argv0_len,
                           r->uri, req.uri_len,
                           r->args, req.args_len);
    } else {
        stat = sock_writev(fd, r, 4,
                           &req, sizeof(req),
                           r->filename, req.filename_len,
                           argv0, req.argv0_len,
                           r->uri, req.uri_len);
    }

    if (stat != APR_SUCCESS) {
        return stat;
    }

    /* write the environment variables */
    for (i = 0; i < req.env_count; i++) {
        apr_size_t curlen = strlen(env[i]);

        if ((stat = sock_writev(fd, r, 2, &curlen, sizeof(curlen),
                                env[i], curlen)) != APR_SUCCESS) {
            return stat;
        }
    }
#if defined(RLIMIT_CPU) && defined(AP_CGID_USE_RLIMIT)
    if (core_conf->limit_cpu) {
        req.limits.limit_cpu = *(core_conf->limit_cpu);
        req.limits.limit_cpu_set = 1;
    }
    else {
        req.limits.limit_cpu_set = 0;
    }
#endif

#if defined(AP_CGID_USE_RLIMIT) && (defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS))
    if (core_conf->limit_mem) {
        req.limits.limit_mem = *(core_conf->limit_mem);
        req.limits.limit_mem_set = 1;
    }
    else {
        req.limits.limit_mem_set = 0;
    }

#endif

#if defined(RLIMIT_NPROC) && defined(AP_CGID_USE_RLIMIT)
    if (core_conf->limit_nproc) {
        req.limits.limit_nproc = *(core_conf->limit_nproc);
        req.limits.limit_nproc_set = 1;
    }
    else {
        req.limits.limit_nproc_set = 0;
    }
#endif

#ifdef AP_CGID_USE_RLIMIT
    if ( (stat = sock_write(fd, &(req.limits), sizeof(cgid_rlimit_t))) != APR_SUCCESS)
        return stat;
#endif

    return APR_SUCCESS;
}