void
redirectInit(void)
{
    static bool init = false;

    if (!init) {
        Mgr::RegisterAction("redirector", "URL Redirector Stats", redirectStats, 0, 1);
        Mgr::RegisterAction("store_id", "StoreId helper Stats", storeIdStats, 0, 1);
    }

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

    if (Config.redirector_extras) {
        delete redirectorExtrasFmt;
        redirectorExtrasFmt = new ::Format::Format("url_rewrite_extras");
        (void)redirectorExtrasFmt->parse(Config.redirector_extras);
    }

    if (Config.storeId_extras) {
        delete storeIdExtrasFmt;
        storeIdExtrasFmt = new ::Format::Format("store_id_extras");
        (void)storeIdExtrasFmt->parse(Config.storeId_extras);
    }

    init = true;
}