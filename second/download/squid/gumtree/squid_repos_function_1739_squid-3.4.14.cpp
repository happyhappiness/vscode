void
dnsInit(void)
{
    wordlist *w;

    dnsRegisterWithCacheManager();

    if (!Config.Program.dnsserver)
        return;

    if (dnsservers == NULL)
        dnsservers = new helper("dnsserver");

    dnsservers->childs.updateLimits(Config.dnsChildren);

    dnsservers->ipc_type = IPC_STREAM;

    assert(dnsservers->cmdline == NULL);

    wordlistAdd(&dnsservers->cmdline, Config.Program.dnsserver);

    if (Config.onoff.res_defnames)
        wordlistAdd(&dnsservers->cmdline, "-D");

    for (w = Config.dns_nameservers; w != NULL; w = w->next) {
        wordlistAdd(&dnsservers->cmdline, "-s");
        wordlistAdd(&dnsservers->cmdline, w->key);
    }

    helperOpenServers(dnsservers);
}