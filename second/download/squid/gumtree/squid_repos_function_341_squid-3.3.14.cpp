int
main(int argc, char *argv[])
{
    my_program_name = argv[0];

    process_options(argc, argv);

    debug("%s build " __DATE__ ", " __TIME__ " starting up...\n", my_program_name);

    if (LoadSecurityDll(SSP_NTLM, NTLM_PACKAGE_NAME) == NULL) {
        fprintf(stderr, "FATAL, can't initialize SSPI, exiting.\n");
        exit(1);
    }
    debug("SSPI initialized OK\n");

    atexit(UnloadSecurityDll);

    /* initialize FDescs */
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    while (manage_request()) {
        /* everything is done within manage_request */
    }
    exit(0);
}