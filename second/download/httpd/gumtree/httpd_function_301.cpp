int main(int argc, const char * const argv[])
{
    apr_file_t *f;
    apr_status_t rv;
    char tn[] = "htdigest.tmp.XXXXXX";
    char user[MAX_STRING_LEN];
    char realm[MAX_STRING_LEN];
    char line[MAX_STRING_LEN];
    char l[MAX_STRING_LEN];
    char w[MAX_STRING_LEN];
    char x[MAX_STRING_LEN];
    char command[MAX_STRING_LEN];
    int found;
   
    apr_app_initialize(&argc, &argv, NULL);
    atexit(terminate); 
    apr_pool_create(&cntxt, NULL);

#if APR_CHARSET_EBCDIC
    rv = apr_xlate_open(&to_ascii, "ISO8859-1", APR_DEFAULT_CHARSET, cntxt);
    if (rv) {
        fprintf(stderr, "apr_xlate_open(): %s (%d)\n",
                apr_strerror(rv, line, sizeof(line)), rv);
        exit(1);
    }
#endif
    
    apr_signal(SIGINT, (void (*)(int)) interrupted);
    if (argc == 5) {
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

    if (apr_file_mktemp(&tfp, tn, 0, cntxt) != APR_SUCCESS) {
	fprintf(stderr, "Could not open temp file.\n");
	exit(1);
    }

    if (apr_file_open(&f, argv[1], APR_READ, -1, cntxt) != APR_SUCCESS) {
	fprintf(stderr,
		"Could not open passwd file %s for reading.\n", argv[1]);
	fprintf(stderr, "Use -c option to create new one.\n");
	exit(1);
    }
    strcpy(user, argv[3]);
    strcpy(realm, argv[2]);

    found = 0;
    while (!(get_line(line, MAX_STRING_LEN, f))) {
	if (found || (line[0] == '#') || (!line[0])) {
	    putline(tfp, line);
	    continue;
	}
	strcpy(l, line);
	getword(w, l, ':');
	getword(x, l, ':');
	if (strcmp(user, w) || strcmp(realm, x)) {
	    putline(tfp, line);
	    continue;
	}
	else {
	    printf("Changing password for user %s in realm %s\n", user, realm);
	    add_password(user, realm, tfp);
	    found = 1;
	}
    }
    if (!found) {
	printf("Adding user %s in realm %s\n", user, realm);
	add_password(user, realm, tfp);
    }
    apr_file_close(f);
#if defined(OS2) || defined(WIN32)
    sprintf(command, "copy \"%s\" \"%s\"", tn, argv[1]);
#else
    sprintf(command, "cp %s %s", tn, argv[1]);
#endif
    system(command);
    apr_file_close(tfp);
    return 0;
}