static void
dump_UrlHelperTimeout(StoreEntry *entry, const char *name, SquidConfig::UrlHelperTimeout &config)
{
    const char  *onTimedOutActions[] = {"bypass", "fail", "retry", "use_configured_response"};
    assert(config.action >= 0 && config.action <= toutActUseConfiguredResponse);

    dump_time_t(entry, name, Config.Timeout.urlRewrite);
    storeAppendPrintf(entry, " on_timeout=%s", onTimedOutActions[config.action]);

    if (config.response)
        storeAppendPrintf(entry, " response=\"%s\"", config.response);

    storeAppendPrintf(entry, "\n");
}