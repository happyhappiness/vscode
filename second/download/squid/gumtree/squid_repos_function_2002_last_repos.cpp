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

        // BACKWARD COMPATIBILITY:
        // if redirectot_bypass is set then use queue_size=0 as default size
        if (Config.onoff.redirector_bypass && Config.redirectChildren.defaultQueueSize)
            Config.redirectChildren.queue_size = 0;

        redirectors->childs.updateLimits(Config.redirectChildren);

        redirectors->ipc_type = IPC_STREAM;

        redirectors->timeout = Config.Timeout.urlRewrite;

        redirectors->retryTimedOut = (Config.onUrlRewriteTimeout.action == toutActRetry);
        redirectors->retryBrokenHelper = true; // XXX: make this configurable ?
        redirectors->onTimedOutResponse.clear();
        if (Config.onUrlRewriteTimeout.action == toutActUseConfiguredResponse)
            redirectors->onTimedOutResponse.assign(Config.onUrlRewriteTimeout.response);

        helperOpenServers(redirectors);
    }

    if (Config.Program.store_id) {

        if (storeIds == NULL)
            storeIds = new helper("store_id");

        storeIds->cmdline = Config.Program.store_id;

        // BACKWARD COMPATIBILITY:
        // if store_id_bypass is set then use queue_size=0 as default size
        if (Config.onoff.store_id_bypass && Config.storeIdChildren.defaultQueueSize)
            Config.storeIdChildren.queue_size = 0;

        storeIds->childs.updateLimits(Config.storeIdChildren);

        storeIds->ipc_type = IPC_STREAM;

        storeIds->retryBrokenHelper = true; // XXX: make this configurable ?

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