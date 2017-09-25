	if (strcmp(argv[1], "-c"))
	    usage();
	rv = apr_file_open(&f, argv[2], APR_WRITE | APR_CREATE, -1, cntxt);
        if (rv != APR_SUCCESS) {
            char errmsg[120];

	    fprintf(stderr, "Could not open passwd file %s for writing: %s\n",
		    argv[2],
                    apr_strerror(rv, errmsg, sizeof errmsg));
	    exit(1);
	}
	printf("Adding password for %s in realm %s.\n", argv[4], argv[3]);
	add_password(argv[4], argv[3], f);
	apr_file_close(f);
	exit(0);
    }
    else if (argc != 4)
	usage();

    if (apr_file_mktemp(&tfp, tn,
#ifdef OMIT_DELONCLOSE
    APR_CREATE | APR_READ | APR_WRITE | APR_EXCL
#else
    0
#endif
    , cntxt) != APR_SUCCESS) {
	fprintf(stderr, "Could not open temp file.\n");
	exit(1);
    }

    if (apr_file_open(&f, argv[1], APR_READ, -1, cntxt) != APR_SUCCESS) {
	fprintf(stderr,
		"Could not open passwd file %s for reading.\n", argv[1]);
	fprintf(stderr, "Use -c option to create new one.\n");
	cleanup_tempfile_and_exit(1);
    }
    apr_cpystrn(user, argv[3], sizeof(user));
    apr_cpystrn(realm, argv[2], sizeof(realm));

    found = 0;
