main(int argc, char *argv[])
{
    my_program_name = argv[0];

    process_options(argc, argv);

    debug("%s build " __DATE__ ", " __TIME__ " starting up...\n", my_program_name);

    if (LoadSecurityDll(SSP_NTLM, NEGOTIATE_PACKAGE_NAME) == NULL) {
        fprintf(stderr, "FATAL: %s: can't initialize SSPI, exiting.\n", argv[0]);
        exit(1);
    }
    debug("SSPI initialized OK\n");
