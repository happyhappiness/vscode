    char wstr[HELPER_INPUT_BUFFER];
    char username[256];
    char password[256];
    char *p;
    int err = 0;

    my_program_name = argv[0];
    process_options(argc, argv);

    if (LoadSecurityDll(SSP_BASIC, NTLM_PACKAGE_NAME) == NULL) {
        fprintf(stderr, "FATAL: can't initialize SSPI, exiting.\n");
        exit(1);
    }
