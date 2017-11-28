void
redirectInit(void)
{
    static int init = 0;

    redirectRegisterWithCacheManager();

    if (!Config.Program.redirect)
        return;

    if (redirectors == NULL)
        redirectors = new helper("redirector");

    redirectors->cmdline = Config.Program.redirect;

    redirectors->childs.updateLimits(Config.redirectChildren);

    redirectors->ipc_type = IPC_STREAM;

    helperOpenServers(redirectors);

    if (!init) {
        init = 1;
        CBDATA_INIT_TYPE(redirectStateData);
    }
}