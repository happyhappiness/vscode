
    if (Config.onoff.httpd_suppress_version_string)
        visible_appname_string = (char *)appname_string;
    else
        visible_appname_string = (char const *)APP_FULLNAME;

#if USE_DNSSERVERS

    if (Config.dnsChildren < 1)
        fatal("No dnsservers allocated");

#endif

    if (Config.Program.redirect) {
        if (Config.redirectChildren < 1) {
            Config.redirectChildren = 0;
            wordlistDestroy(&Config.Program.redirect);
        }
    }

    if (Config.appendDomain)
        if (*Config.appendDomain != '.')
