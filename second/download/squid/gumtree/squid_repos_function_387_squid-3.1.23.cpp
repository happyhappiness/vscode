int
main(int argc, char **argv)

{
    char wstr[256];
    char username[256];
    char password[256];
    char *p;
    int err = 0;

    my_program_name = argv[0];
    process_options(argc, argv);

    debug("%s build " __DATE__ ", " __TIME__ " starting up...\n", my_program_name);

    if (LoadSecurityDll(SSP_BASIC, NTLM_PACKAGE_NAME) == NULL) {
        fprintf(stderr, "FATAL, can't initialize SSPI, exiting.\n");
        exit(1);
    }
    debug("SSPI initialized OK\n");

    atexit(UnloadSecurityDll);

    /* initialize FDescs */
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    while (1) {
        /* Read whole line from standard input. Terminate on break. */
        if (fgets(wstr, 255, stdin) == NULL)
            break;

        if (NULL == strchr(wstr, '\n')) {
            err = 1;
            continue;
        }
        if (err) {
            fprintf(stderr, "Oversized message\n");
            puts("ERR");
            goto error;
        }

        if ((p = strchr(wstr, '\n')) != NULL)
            *p = '\0';		/* strip \n */
        if ((p = strchr(wstr, '\r')) != NULL)
            *p = '\0';		/* strip \r */
        /* Clear any current settings */
        username[0] = '\0';
        password[0] = '\0';
        sscanf(wstr, "%s %s", username, password);	/* Extract parameters */

        debug("Got %s from Squid\n", wstr);

        /* Check for invalid or blank entries */
        if ((username[0] == '\0') || (password[0] == '\0')) {
            fprintf(stderr, "Invalid Request\n");
            puts("ERR");
            fflush(stdout);
            continue;
        }
        rfc1738_unescape(username);
        rfc1738_unescape(password);

        debug("Trying to validate; %s %s\n", username, password);

        if (Valid_User(username, password, NTGroup) == NTV_NO_ERROR)
            puts("OK");
        else
            printf("ERR %s\n", errormsg);
error:
        err = 0;
        fflush(stdout);
    }
    return 0;
}