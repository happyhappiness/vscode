int
main(int argc, char *argv[])
{
    char *p;
    char buf[HELPER_INPUT_BUFFER];
    char *username;
    char *group;
    const char *groups[512];
    int n;

    if (argc > 0) {		/* should always be true */
        program_name = strrchr(argv[0], '/');
        if (program_name == NULL)
            program_name = argv[0];
    } else {
        program_name = "(unknown)";
    }
    mypid = getpid();

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    /* Check Command Line */
    process_options(argc, argv);

    if (use_global) {
        if ((machinedomain = GetDomainName()) == NULL) {
            fprintf(stderr, "%s: FATAL: Can't read machine domain\n", program_name);
            exit(1);
        }
        strlwr(machinedomain);
        if (!DefaultDomain)
            DefaultDomain = xstrdup(machinedomain);
    }
    debug("External ACL win32 group helper build " __DATE__ ", " __TIME__
          " starting up...\n");
    if (use_global) {
        debug("Domain Global group mode enabled using '%s' as default domain.\n", DefaultDomain);
    }
    if (use_case_insensitive_compare) {
        debug("Warning: running in case insensitive mode !!!\n");
    }
    if (use_PDC_only) {
        debug("Warning: using only PDCs for group validation !!!\n");
    }

    /* Main Loop */
    while (fgets(buf, HELPER_INPUT_BUFFER, stdin)) {
        if (NULL == strchr(buf, '\n')) {
            /* too large message received.. skip and deny */
            debug("%s: ERROR: Too large: %s\n", argv[0], buf);
            while (fgets(buf, HELPER_INPUT_BUFFER, stdin)) {
                debug("%s: ERROR: Too large..: %s\n", argv[0], buf);
                if (strchr(buf, '\n') != NULL)
                    break;
            }
            SEND_ERR("Input Too Long.");
            continue;
        }
        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';		/* strip \n */
        if ((p = strchr(buf, '\r')) != NULL)
            *p = '\0';		/* strip \r */

        debug("Got '%s' from Squid (length: %d).\n", buf, strlen(buf));

        if (buf[0] == '\0') {
            SEND_ERR("Invalid Request.");
            continue;
        }
        username = strtok(buf, " ");
        for (n = 0; (group = strtok(NULL, " ")) != NULL; ++n) {
            rfc1738_unescape(group);
            groups[n] = group;
        }
        groups[n] = NULL;

        if (NULL == username) {
            SEND_ERR("Invalid Request. No Username.");
            continue;
        }
        rfc1738_unescape(username);

        if ((use_global ? Valid_Global_Groups(username, groups) : Valid_Local_Groups(username, groups))) {
            SEND_OK("");
        } else {
            SEND_ERR("");
        }
    }
    return 0;
}