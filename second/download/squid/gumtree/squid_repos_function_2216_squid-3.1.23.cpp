static void
idnsParseResolvConf(void)
{
    FILE *fp;
    char buf[RESOLV_BUFSZ];
    const char *t;
    fp = fopen(_PATH_RESCONF, "r");

    if (fp == NULL) {
        debugs(78, 1, "" << _PATH_RESCONF << ": " << xstrerror());
        return;
    }

#if defined(_SQUID_CYGWIN_)
    setmode(fileno(fp), O_TEXT);

#endif

    while (fgets(buf, RESOLV_BUFSZ, fp)) {
        t = strtok(buf, w_space);

        if (NULL == t) {
            continue;
        } else if (strcasecmp(t, "nameserver") == 0) {
            t = strtok(NULL, w_space);

            if (NULL == t)
                continue;

            debugs(78, 1, "Adding nameserver " << t << " from " << _PATH_RESCONF);

            idnsAddNameserver(t);
        } else if (strcasecmp(t, "domain") == 0) {
            idnsFreeSearchpath();
            t = strtok(NULL, w_space);

            if (NULL == t)
                continue;

            debugs(78, 1, "Adding domain " << t << " from " << _PATH_RESCONF);

            idnsAddPathComponent(t);
        } else if (strcasecmp(t, "search") == 0) {
            idnsFreeSearchpath();
            while (NULL != t) {
                t = strtok(NULL, w_space);

                if (NULL == t)
                    continue;

                debugs(78, 1, "Adding domain " << t << " from " << _PATH_RESCONF);

                idnsAddPathComponent(t);
            }
        } else if (strcasecmp(t, "options") == 0) {
            while (NULL != t) {
                t = strtok(NULL, w_space);

                if (NULL == t)
                    continue;

                if (strncmp(t, "ndots:", 6) == 0) {
                    ndots = atoi(t + 6);

                    if (ndots < 1)
                        ndots = 1;

                    debugs(78, 1, "Adding ndots " << ndots << " from " << _PATH_RESCONF);
                }
            }
        }
    }
    if (npc == 0 && (t = getMyHostname())) {
        t = strchr(t, '.');
        if (t)
            idnsAddPathComponent(t+1);
    }

    fclose(fp);
}