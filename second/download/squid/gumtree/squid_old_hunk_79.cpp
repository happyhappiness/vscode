     * for substrings in the Via header.
     */
    snprintf(ThisCache2, sizeof(ThisCache), " %s (%s)",
             uniqueHostname(),
             visible_appname_string);

    if (!Config.udpMaxHitObjsz || Config.udpMaxHitObjsz > SQUID_UDP_SO_SNDBUF)
        Config.udpMaxHitObjsz = SQUID_UDP_SO_SNDBUF;

    if (Config.appendDomain)
        Config.appendDomainLen = strlen(Config.appendDomain);
    else
        Config.appendDomainLen = 0;

    if (Config.retry.maxtries > 10)
        fatal("maximum_single_addr_tries cannot be larger than 10");

    if (Config.retry.maxtries < 1) {
        debugs(3, 0, "WARNING: resetting 'maximum_single_addr_tries to 1");
        Config.retry.maxtries = 1;
    }

    requirePathnameExists("MIME Config Table", Config.mimeTablePathname);
#if USE_DNSSERVERS

    requirePathnameExists("cache_dns_program", Config.Program.dnsserver);
#endif
#if USE_UNLINKD

    requirePathnameExists("unlinkd_program", Config.Program.unlinkd);
#endif

    if (Config.Program.redirect)
        requirePathnameExists("redirect_program", Config.Program.redirect->key);

    requirePathnameExists("Icon Directory", Config.icons.directory);

    if (Config.errorDirectory)
        requirePathnameExists("Error Directory", Config.errorDirectory);

#if HTTP_VIOLATIONS

    {
        const refresh_t *R;

        for (R = Config.Refresh; R; R = R->next) {
            if (!R->flags.override_expire)
