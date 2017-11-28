void
redirectInit(void)
{
    static int init = 0;

    redirectRegisterWithCacheManager();

    /** FIXME: Temporary unified helpers startup
     * When and if needed for more helpers a separated startup
     * method will be added for each of them.
     */
    if (!Config.Program.redirect && !Config.Program.store_id)
        return;

    if (Config.Program.redirect) {

        if (redirectors == NULL)
            redirectors = new helper("redirector");

        redirectors->cmdline = Config.Program.redirect;

        redirectors->childs.updateLimits(Config.redirectChildren);

        redirectors->ipc_type = IPC_STREAM;

        helperOpenServers(redirectors);
    }

    if (Config.Program.store_id) {

        if (storeIds == NULL)
            storeIds = new helper("store_id");

        storeIds->cmdline = Config.Program.store_id;

        storeIds->childs.updateLimits(Config.storeIdChildren);

        storeIds->ipc_type = IPC_STREAM;

        helperOpenServers(storeIds);
    }

    if (!init) {
        init = 1;
        CBDATA_INIT_TYPE(redirectStateData);
    }
}