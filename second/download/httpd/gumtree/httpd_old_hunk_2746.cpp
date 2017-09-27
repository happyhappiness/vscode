}

static int cgid_init(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp,
                     server_rec *main_server)
{
    apr_proc_t *procnew = NULL;
    int first_time = 0;
    const char *userdata_key = "cgid_init";
    module **m;
    int ret = OK;
    void *data;

    root_server = main_server;
    root_pool = p;

    apr_pool_userdata_get(&data, userdata_key, main_server->process->pool);
    if (!data) {
        first_time = 1;
        procnew = apr_pcalloc(main_server->process->pool, sizeof(*procnew));
        procnew->pid = -1;
        procnew->err = procnew->in = procnew->out = NULL;
        apr_pool_userdata_set((const void *)procnew, userdata_key,
                     apr_pool_cleanup_null, main_server->process->pool);
    }
    else {
        procnew = data;
    }

    if (!first_time) {
        total_modules = 0;
        for (m = ap_preloaded_modules; *m != NULL; m++)
            total_modules++;

        parent_pid = getpid();
        sockname = ap_server_root_relative(p, sockname);

        server_addr_len = APR_OFFSETOF(struct sockaddr_un, sun_path) + strlen(sockname);
        server_addr = (struct sockaddr_un *)apr_palloc(p, server_addr_len + 1);
        server_addr->sun_family = AF_UNIX;
        strcpy(server_addr->sun_path, sockname);

