main(int argc, char *argv[])
{
    my_program_name = argv[0];

    process_options(argc, argv);

    debug("%s " VERSION " " SQUID_BUILD_INFO " starting up...\n", my_program_name);

    if (LoadSecurityDll(SSP_NTLM, NTLM_PACKAGE_NAME) == NULL) {
        fprintf(stderr, "FATAL, can't initialize SSPI, exiting.\n");
        exit(1);
    }
    debug("SSPI initialized OK\n");
