static bool
idnsParseResolvConf(void)
{
    bool result = false;
#if !_SQUID_WINDOWS_
    FILE *fp = fopen(_PATH_RESCONF, "r");

    if (!fp) {
        int xerrno = errno;
        debugs(78, DBG_IMPORTANT, "" << _PATH_RESCONF << ": " << xstrerr(xerrno));
        return false;
    }

    char buf[RESOLV_BUFSZ];
    const char *t = NULL;
    while (fgets(buf, RESOLV_BUFSZ, fp)) {
        t = strtok(buf, w_space);

        if (NULL == t) {
            continue;
        } else if (strcmp(t, "nameserver") == 0) {
            t = strtok(NULL, w_space);

            if (NULL == t)
                continue;

            debugs(78, DBG_IMPORTANT, "Adding nameserver " << t << " from " << _PATH_RESCONF);

            idnsAddNameserver(t);
            result = true;
        } else if (strcmp(t, "domain") == 0) {
            idnsFreeSearchpath();
            t = strtok(NULL, w_space);

            if (NULL == t)
                continue;

            debugs(78, DBG_IMPORTANT, "Adding domain " << t << " from " << _PATH_RESCONF);

            idnsAddPathComponent(t);
        } else if (strcmp(t, "search") == 0) {
            idnsFreeSearchpath();
            while (NULL != t) {
                t = strtok(NULL, w_space);

                if (NULL == t)
                    continue;

                debugs(78, DBG_IMPORTANT, "Adding domain " << t << " from " << _PATH_RESCONF);

                idnsAddPathComponent(t);
            }
        } else if (strcmp(t, "options") == 0) {
            while (NULL != t) {
                t = strtok(NULL, w_space);

                if (NULL == t)
                    continue;

                if (strncmp(t, "ndots:", 6) == 0) {
                    ndots = atoi(t + 6);

                    if (ndots < 1)
                        ndots = 1;

                    debugs(78, DBG_IMPORTANT, "Adding ndots " << ndots << " from " << _PATH_RESCONF);
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
#endif
    return result;
}