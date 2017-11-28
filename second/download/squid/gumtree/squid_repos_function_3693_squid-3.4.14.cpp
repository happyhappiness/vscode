int
main(int argc, char *argv[])
{
    char request[512];
    char *t = NULL;
    int c;
    int opt_s = 0;

#if HAVE_RES_INIT
    res_init();
#endif

#if USE_IPV6
    /* perform AAAA lookups *before* A lookups in IPv6 mode. */
    _res.options |= RES_USE_INET6;
#endif

    while ((c = getopt(argc, argv, "Dhs:v")) != -1) {
        switch (c) {

        case 'D':
            fprintf(stderr, "-D is now default behaviour from this tool.\n");
            break;

        case 's':
            squid_res_setservers(opt_s);
            opt_s = 1;
            break;

        case 'v':
            printf("dnsserver version %s\n", VERSION);

            exit(0);

            break;

        case 'h':

        default:
            usage();

            exit(1);

            break;
        }
    }

#if _SQUID_WINDOWS_
    {
        WSADATA wsaData;

        WSAStartup(2, &wsaData);
    }

    fflush(stderr);
#endif

    for (;;) {
        memset(request, '\0', REQ_SZ);

        if (fgets(request, REQ_SZ, stdin) == NULL) {
#if _SQUID_WINDOWS_
            WSACleanup();
#endif
            exit(1);
        }

        t = strrchr(request, '\n');

        if (t == NULL)		/* Ignore if no newline */
            continue;

        *t = '\0';		/* strip NL */

        if ((t = strrchr(request, '\r')) != NULL)
            *t = '\0';		/* strip CR */

        lookup(request);

        fflush(stdout);
    }

    /* NOTREACHED */
    return 0;
}