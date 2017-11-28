int
main(int argc, char *argv[])
{
    char buf[HELPER_INPUT_BUFFER];
    int buflen = 0;

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    program_name = argv[0];

    process_options(argc, argv);

    debug("%s build " __DATE__ ", " __TIME__ " starting up...\n", program_name);

    while (fgets(buf, HELPER_INPUT_BUFFER, stdin) != NULL) {
        char *p;

        if ((p = strchr(buf, '\n')) != NULL) {
            *p = '\0';		/* strip \n */
            buflen = p - buf;   /* length is known already */
        } else
            buflen = strlen(buf);   /* keep this so we only scan the buffer for \0 once per loop */

        debug("Got %d bytes '%s' from Squid\n", buflen, buf);

        /* send 'OK' result back to Squid */
        SEND_OK("");
    }
    debug("%s build " __DATE__ ", " __TIME__ " shutting down...\n", program_name);
    exit(0);
}