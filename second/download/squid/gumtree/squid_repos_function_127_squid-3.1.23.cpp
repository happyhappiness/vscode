int
main(int argc, char *argv[])
{
    char *p;
    char buf[BUFSIZE];
    char *username;
    char *group;
    int err = 0;
    const char *groups[512];
    int n;

    if (argc > 0) {		/* should always be true */
        myname = strrchr(argv[0], '/');
        if (myname == NULL)
            myname = argv[0];
    } else {
        myname = "(unknown)";
    }
    mypid = getpid();

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    /* Check Command Line */
    process_options(argc, argv);

    if (use_global) {
        if ((machinedomain = GetDomainName()) == NULL) {
            fprintf(stderr, "%s Can't read machine domain\n", myname);
            exit(1);
        }
        strlwr(machinedomain);
        if (!DefaultDomain)
            DefaultDomain = xstrdup(machinedomain);
    }
    debug("External ACL win32 group helper build " __DATE__ ", " __TIME__
          " starting up...\n");
    if (use_global)
        debug("Domain Global group mode enabled using '%s' as default domain.\n", DefaultDomain);
    if (use_case_insensitive_compare)
        debug("Warning: running in case insensitive mode !!!\n");

    /* Main Loop */
    while (fgets(buf, sizeof(buf), stdin)) {
        if (NULL == strchr(buf, '\n')) {
            /* too large message received.. skip and deny */
            fprintf(stderr, "%s: ERROR: Too large: %s\n", argv[0], buf);
            while (fgets(buf, sizeof(buf), stdin)) {
                fprintf(stderr, "%s: ERROR: Too large..: %s\n", argv[0], buf);
                if (strchr(buf, '\n') != NULL)
                    break;
            }
            goto error;
        }
        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';		/* strip \n */
        if ((p = strchr(buf, '\r')) != NULL)
            *p = '\0';		/* strip \r */

        debug("Got '%s' from Squid (length: %d).\n", buf, strlen(buf));

        if (buf[0] == '\0') {
            fprintf(stderr, "Invalid Request\n");
            goto error;
        }
        username = strtok(buf, " ");
        for (n = 0; (group = strtok(NULL, " ")) != NULL; n++) {
            rfc1738_unescape(group);
            groups[n] = group;
        }
        groups[n] = NULL;

        if (NULL == username) {
            fprintf(stderr, "Invalid Request\n");
            goto error;
        }
        rfc1738_unescape(username);

        if ((use_global ? Valid_Global_Groups(username, groups) : Valid_Local_Groups(username, groups))) {
            printf("OK\n");
        } else {
error:
            printf("ERR\n");
        }
        err = 0;
    }
    return 0;
}