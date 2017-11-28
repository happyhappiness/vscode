void
redirectInit(void)
{
    static int init = 0;

    redirectRegisterWithCacheManager();

    if (!Config.Program.redirect)
        return;

    if (redirectors == NULL)
        redirectors = helperCreate("redirector");

    redirectors->cmdline = Config.Program.redirect;

    redirectors->n_to_start = Config.redirectChildren;

    redirectors->concurrency = Config.redirectConcurrency;

    redirectors->ipc_type = IPC_STREAM;

    helperOpenServers(redirectors);

    if (!init) {
        init = 1;
        CBDATA_INIT_TYPE(redirectStateData);
    }
}