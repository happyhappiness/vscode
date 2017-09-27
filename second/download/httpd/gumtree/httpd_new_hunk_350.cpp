	if (strcmp(argv[1], "-c"))
	    usage();
	rv = apr_file_open(&f, argv[2], APR_WRITE | APR_CREATE, -1, cntxt);
        if (rv != APR_SUCCESS) {
            char errmsg[120];

            apr_file_printf(errfile, "Could not open passwd file %s for writing: %s\n",
		    argv[2],
                    apr_strerror(rv, errmsg, sizeof errmsg));
	    exit(1);
	}
        apr_file_printf(errfile, "Adding password for %s in realm %s.\n", 
                    argv[4], argv[3]);
	add_password(argv[4], argv[3], f);
	apr_file_close(f);
	exit(0);
    }
    else if (argc != 4)
	usage();

    if (apr_temp_dir_get((const char**)&dirname, cntxt) != APR_SUCCESS) {
        apr_file_printf(errfile, "%s: could not determine temp dir\n",
                        argv[0]);
        exit(1);
    }
    dirname = apr_psprintf(cntxt, "%s/%s", dirname, tn);

    if (apr_file_mktemp(&tfp, dirname, 0, cntxt) != APR_SUCCESS) {
        apr_file_printf(errfile, "Could not open temp file %s.\n", dirname);
	exit(1);
    }

    if (apr_file_open(&f, argv[1], APR_READ, -1, cntxt) != APR_SUCCESS) {
        apr_file_printf(errfile,
		"Could not open passwd file %s for reading.\n", argv[1]);
        apr_file_printf(errfile, "Use -c option to create new one.\n");
        cleanup_tempfile_and_exit(1);
    }
    apr_cpystrn(user, argv[3], sizeof(user));
    apr_cpystrn(realm, argv[2], sizeof(realm));

    found = 0;
    while (!(get_line(line, MAX_STRING_LEN, f))) {
	if (found || (line[0] == '#') || (!line[0])) {
	    putline(tfp, line);
	    continue;
