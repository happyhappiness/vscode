int main (int argc, char *argv[])
{
    struct in_addr ipnum;
    char *bar, hoststring[MAXDNAME + 1], line[MAXLINE], *statfile;
    int i, check;

#if defined(WIN32) || (defined(NETWARE) && defined(USE_WINSOCK))
    /*  If we apr'ify this code, apr_pool_create/apr_pool_destroy
     *  should perform the WSAStartup/WSACleanup for us.
     */
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif

    check = 0;
    statfile = NULL;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0)
            check = 1;
        else if (strcmp(argv[i], "-s") == 0) {
            if (i == argc - 1) {
                fprintf(stderr, "logresolve: missing filename to -s\n");
                exit(1);
            }
            i++;
            statfile = argv[i];
        }
        else {
            fprintf(stderr, "Usage: logresolve [-s statfile] [-c] < input > output\n");
            exit(0);
        }
    }

    for (i = 0; i < BUCKETS; i++)
        nscache[i] = NULL;
    for (i = 0; i < MAX_ERR + 2; i++)
        errors[i] = 0;

    while (get_line(line, MAXLINE)) {
        if (line[0] == '\0')
            continue;
        entries++;
        if (!apr_isdigit(line[0])) {  /* short cut */
            puts(line);
            withname++;
            continue;
        }
        bar = strchr(line, ' ');
        if (bar != NULL)
            *bar = '\0';
        ipnum.s_addr = inet_addr(line);
        if (ipnum.s_addr == 0xffffffffu) {
            if (bar != NULL)
                *bar = ' ';
            puts(line);
            withname++;
            continue;
        }

        resolves++;

        cgethost(ipnum, hoststring, check);
        if (bar != NULL)
            printf("%s %s\n", hoststring, bar + 1);
        else
            puts(hoststring);
    }

#if defined(WIN32) || (defined(NETWARE) && defined(USE_WINSOCK))
     WSACleanup();
#endif

    if (statfile != NULL) {
        FILE *fp;
        fp = fopen(statfile, "w");
        if (fp == NULL) {
            fprintf(stderr, "logresolve: could not open statistics file '%s'\n"
                    ,statfile);
            exit(1);
        }
        stats(fp);
        fclose(fp);
    }

    return (0);
}