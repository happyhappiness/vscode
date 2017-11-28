static int
check_target_acl(const char *hostname, int port)
{
    char config_line[BUFSIZ];
    FILE *fp = NULL;
    int ret = 0;
    fp = fopen("cachemgr.conf", "r");

    if (fp == NULL)
        fp = fopen(DEFAULT_CACHEMGR_CONFIG, "r");

    if (fp == NULL) {
#ifdef CACHEMGR_HOSTNAME_DEFINED

        if (strcmp(hostname, CACHEMGR_HOSTNAME) == 0 && port == CACHE_HTTP_PORT)
            return 1;

#else

        if (strcmp(hostname, "localhost") == 0)
            return 1;

        if (strcmp(hostname, getfullhostname()) == 0)
            return 1;

#endif

        return 0;
    }

    while (fgets(config_line, BUFSIZ, fp)) {
        char *token = NULL;
        strtok(config_line, " \r\n\t");

        if (config_line[0] == '#')
            continue;

        if (config_line[0] == '\0')
            continue;

        if ((token = strtok(config_line, ":")) == NULL)
            continue;

#if HAVE_FNMATCH_H

        if (fnmatch(token, hostname, 0) != 0)
            continue;

#else

        if (strcmp(token, hostname) != 0)
            continue;

#endif

        if ((token = strtok(NULL, ":")) != NULL) {
            int i;

            if (strcmp(token, "*") == 0)

                ;   /* Wildcard port specification */
            else if (strcmp(token, "any") == 0)

                ;   /* Wildcard port specification */
            else if (sscanf(token, "%d", &i) != 1)
                continue;

            else if (i != port)
                continue;
        } else if (port != CACHE_HTTP_PORT)
            continue;

        ret = 1;

        break;
    }

    fclose(fp);
    return ret;
}