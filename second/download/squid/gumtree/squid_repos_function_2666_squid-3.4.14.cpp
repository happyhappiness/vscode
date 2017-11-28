void
parseEtcHosts(void)
{
    FILE *fp;
    char buf[1024];
    char buf2[512];
    char *nt = buf;
    char *lt = buf;

    if (NULL == Config.etcHostsPath)
        return;

    if (0 == strcmp(Config.etcHostsPath, "none"))
        return;

    fp = fopen(Config.etcHostsPath, "r");

    if (fp == NULL) {
        debugs(1, DBG_IMPORTANT, "parseEtcHosts: " << Config.etcHostsPath << ": " << xstrerror());
        return;
    }

#if _SQUID_WINDOWS_
    setmode(fileno(fp), O_TEXT);
#endif

    while (fgets(buf, 1024, fp)) {	/* for each line */
        wordlist *hosts = NULL;
        char *addr;

        if (buf[0] == '#')	/* MS-windows likes to add comments */
            continue;

        strtok(buf, "#");	/* chop everything following a comment marker */

        lt = buf;

        addr = buf;

        debugs(1, 5, "etc_hosts: line is '" << buf << "'");

        nt = strpbrk(lt, w_space);

        if (nt == NULL)		/* empty line */
            continue;

        *nt = '\0';		/* null-terminate the address */

        debugs(1, 5, "etc_hosts: address is '" << addr << "'");

        lt = nt + 1;

        while ((nt = strpbrk(lt, w_space))) {
            char *host = NULL;

            if (nt == lt) {	/* multiple spaces */
                debugs(1, 5, "etc_hosts: multiple spaces, skipping");
                lt = nt + 1;
                continue;
            }

            *nt = '\0';
            debugs(1, 5, "etc_hosts: got hostname '" << lt << "'");

            /* For IPV6 addresses also check for a colon */
            if (Config.appendDomain && !strchr(lt, '.') && !strchr(lt, ':')) {
                /* I know it's ugly, but it's only at reconfig */
                strncpy(buf2, lt, sizeof(buf2)-1);
                strncat(buf2, Config.appendDomain, sizeof(buf2) - strlen(lt) - 1);
                buf2[sizeof(buf2)-1] = '\0';
                host = buf2;
            } else {
                host = lt;
            }

            if (ipcacheAddEntryFromHosts(host, addr) != 0) {
                /* invalid address, continuing is useless */
                wordlistDestroy(&hosts);
                hosts = NULL;
                break;
            }
            wordlistAdd(&hosts, host);

            lt = nt + 1;
        }

        if (hosts) {
            fqdncacheAddEntryFromHosts(addr, hosts);
            wordlistDestroy(&hosts);
        }
    }

    fclose (fp);
}