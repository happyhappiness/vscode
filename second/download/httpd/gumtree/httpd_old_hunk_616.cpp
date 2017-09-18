	arg = argv[i];
	if (*arg != '-') {
	    break;
	}
	while (*++arg != '\0') {
	    if (*arg == 'c') {
		newfile++;
	    }
	    else if (*arg == 'n') {
		nofile++;
		args_left--;
	    }
	    else if (*arg == 'm') {
		alg = ALG_APMD5;
	    }
	    else if (*arg == 's') {
		alg = ALG_APSHA;
	    }
	    else if (*arg == 'p') {
		alg = ALG_PLAIN;
	    }
	    else if (*arg == 'd') {
		alg = ALG_CRYPT;
	    }
	    else if (*arg == 'b') {
		noninteractive++;
		args_left++;
	    }
	    else {
		return usage();
	    }
	}
    }

    /*
     * Make sure we still have exactly the right number of arguments left
     * (the filename, the username, and possibly the password if -b was
     * specified).
     */
    if ((argc - i) != args_left) {
	return usage();
    }
    if (newfile && nofile) {
	fprintf(stderr, "%s: -c and -n options conflict\n", argv[0]);
	return ERR_SYNTAX;
    }
    if (nofile) {
	i--;
    }
    else {
	if (strlen(argv[i]) > (sizeof(pwfilename) - 1)) {
	    fprintf(stderr, "%s: filename too long\n", argv[0]);
	    return ERR_OVERFLOW;
	}
	strcpy(pwfilename, argv[i]);
	if (strlen(argv[i + 1]) > (sizeof(user) - 1)) {
	    fprintf(stderr, "%s: username too long (>%" APR_SIZE_T_FMT ")\n",
	        argv[0], sizeof(user) - 1);
	    return ERR_OVERFLOW;
	}
    }
    strcpy(user, argv[i + 1]);
    if ((arg = strchr(user, ':')) != NULL) {
	fprintf(stderr, "%s: username contains illegal character '%c'\n",
		argv[0], *arg);
	return ERR_BADUSER;
    }
    if (noninteractive) {
	if (strlen(argv[i + 2]) > (sizeof(password) - 1)) {
	    fprintf(stderr, "%s: password too long (>%" APR_SIZE_T_FMT ")\n",
	        argv[0], sizeof(password) - 1);
	    return ERR_OVERFLOW;
	}
	strcpy(password, argv[i + 2]);
    }

#if defined(WIN32) || defined(NETWARE)
    if (alg == ALG_CRYPT) {
	alg = ALG_APMD5;
	fprintf(stderr, "Automatically using MD5 format.\n");
    }
#endif

#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
    if (alg == ALG_PLAIN) {
	fprintf(stderr,"Warning: storing passwords as plain text might "
		"just not work on this platform.\n");
    }
#endif
    if (! nofile) {
	/*
	 * Only do the file checks if we're supposed to frob it.
	 *
	 * Verify that the file exists if -c was omitted.  We give a special
	 * message if it doesn't.
	 */
	if ((! newfile) && (! exists(pwfilename, pool))) {
	    fprintf(stderr,
		    "%s: cannot modify file %s; use '-c' to create it\n",
		    argv[0], pwfilename);
	    perror("fopen");
	    exit(ERR_FILEPERM);
	}
	/*
	 * Verify that we can read the existing file in the case of an update
	 * to it (rather than creation of a new one).
	 */
	if ((! newfile) && (! readable(pwfilename))) {
	    fprintf(stderr, "%s: cannot open file %s for read access\n",
		    argv[0], pwfilename);
	    perror("fopen");
	    exit(ERR_FILEPERM);
	}
	/*
	 * Now check to see if we can preserve an existing file in case
	 * of password verification errors on a -c operation.
	 */
	if (newfile && exists(pwfilename, pool) && (! readable(pwfilename))) {
	    fprintf(stderr, "%s: cannot open file %s for read access\n"
		    "%s: existing auth data would be lost on "
		    "password mismatch",
		    argv[0], pwfilename, argv[0]);
	    perror("fopen");
	    exit(ERR_FILEPERM);
	}
	/*
	 * Now verify that the file is writable!
	 */
	if (! writable(pwfilename)) {
	    fprintf(stderr, "%s: cannot open file %s for write access\n",
		    argv[0], pwfilename);
	    perror("fopen");
	    exit(ERR_FILEPERM);
	}
    }

    /*
     * All the file access checks (if any) have been made.  Time to go to work;
     * try to create the record for the username in question.  If that
     * fails, there's no need to waste any time on file manipulations.
     * Any error message text is returned in the record buffer, since
     * the mkrecord() routine doesn't have access to argv[].
     */
    i = mkrecord(user, record, sizeof(record) - 1,
		 noninteractive ? password : NULL,
		 alg);
    if (i != 0) {
	fprintf(stderr, "%s: %s\n", argv[0], record);
	exit(i);
    }
    if (nofile) {
	printf("%s\n", record);
	exit(0);
    }

    /*
     * We can access the files the right way, and we have a record
     * to add or update.  Let's do it..
     */
    errno = 0;
    tempfilename = tmpnam(tname_buf);
    if ((tempfilename == NULL) || (*tempfilename == '\0')) {
	fprintf(stderr, "%s: unable to generate temporary filename\n",
		argv[0]);
	if (errno == 0) {
	    errno = ENOENT;
	}
	perror("tmpnam");
	exit(ERR_FILEPERM);
    }
    ftemp = fopen(tempfilename, "w+");
    if (ftemp == NULL) {
	fprintf(stderr, "%s: unable to create temporary file '%s'\n", argv[0],
		tempfilename);
	perror("fopen");
	exit(ERR_FILEPERM);
    }
    /*
     * If we're not creating a new file, copy records from the existing
     * one to the temporary file until we find the specified user.
     */
    if (! newfile) {
	char scratch[MAX_STRING_LEN];

	fpw = fopen(pwfilename, "r");
	while (! (getline(line, sizeof(line), fpw))) {
	    char *colon;

	    if ((line[0] == '#') || (line[0] == '\0')) {
		putline(ftemp, line);
		continue;
	    }
