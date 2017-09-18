    if (apr_file_open(&f, argv[1], APR_READ, -1, cntxt) != APR_SUCCESS) {
	fprintf(stderr,
		"Could not open passwd file %s for reading.\n", argv[1]);
	fprintf(stderr, "Use -c option to create new one.\n");
	cleanup_tempfile_and_exit(1);
    }
    apr_cpystrn(user, argv[3], sizeof(user));
    apr_cpystrn(realm, argv[2], sizeof(realm));

    found = 0;
    while (!(get_line(line, MAX_STRING_LEN, f))) {
	if (found || (line[0] == '#') || (!line[0])) {
	    putline(tfp, line);
	    continue;
