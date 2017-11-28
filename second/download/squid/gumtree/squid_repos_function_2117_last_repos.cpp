void
parseEtcHosts(void)
{
    char buf[1024];
    char buf2[512];
    char *nt = buf;
    char *lt = buf;

    if (!Config.etcHostsPath)
        return;

    if (0 == strcmp(Config.etcHostsPath, "none"))
        return;

    FILE *fp = fopen(Config.etcHostsPath, "r");

    if (!fp) {
        int xerrno = errno;
        debugs(1, DBG_IMPORTANT, "parseEtcHosts: '" << Config.etcHostsPath << "' : " << xstrerr(xerrno));
        return;
    }

#if _SQUID_WINDOWS_
    setmode(fileno(fp), O_TEXT);
#endif

    while (fgets(buf, 1024, fp)) {  /* for each line */

        if (buf[0] == '#')  /* MS-windows likes to add comments */
            continue;

        strtok(buf, "#");   /* chop everything following a comment marker */

        lt = buf;

        char *addr = buf;

        debugs(1, 5, "etc_hosts: line is '" << buf << "'");

        nt = strpbrk(lt, w_space);

        if (nt == NULL)     /* empty line */
            continue;

        *nt = '\0';     /* null-terminate the address */

        debugs(1, 5, "etc_hosts: address is '" << addr << "'");

        lt = nt + 1;

        SBufList hosts;

        while ((nt = strpbrk(lt, w_space))) {
            char *host = NULL;

            if (nt == lt) { /* multiple spaces */
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
                hosts.clear();
                break;
            }
            hosts.emplace_back(SBuf(host));

            lt = nt + 1;
        }

        if (!hosts.empty())
            fqdncacheAddEntryFromHosts(addr, hosts);
    }

    fclose (fp);
}