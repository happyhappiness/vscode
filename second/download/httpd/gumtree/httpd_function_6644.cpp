int main(int argc, const char * const argv[])
{
    apr_file_t *f;
    apr_status_t rv;
    char tn[] = "htdigest.tmp.XXXXXX";
    char *dirname;
    char user[MAX_STRING_LEN];
    char realm[MAX_STRING_LEN];
    char line[3 * MAX_STRING_LEN];
    char l[3 * MAX_STRING_LEN];
    char w[MAX_STRING_LEN];
    char x[MAX_STRING_LEN];
    int found;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(terminate);
    apr_pool_create(&cntxt, NULL);
    apr_file_open_stderr(&errfile, cntxt);

#if APR_CHARSET_EBCDIC
    rv = apr_xlate_open(&to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, cntxt);
    if (rv) {
        apr_file_printf(errfile, "apr_xlate_open(): %s (%d)\n",
                apr_strerror(rv, line, sizeof(line)), rv);
        exit(1);
    }
#endif

    apr_signal(SIGINT, (void (*)(int)) interrupted);
    if (argc == 5) {
        if (strcmp(argv[1], "-c"))
            usage();
        rv = apr_file_open(&f, argv[2], APR_WRITE | APR_CREATE,
                           APR_OS_DEFAULT, cntxt);
        if (rv != APR_SUCCESS) {
            char errmsg[120];

            apr_file_printf(errfile, "Could not open passwd file %s for writing: %s\n",
                    argv[2],
                    apr_strerror(rv, errmsg, sizeof errmsg));
            exit(1);
        }
        apr_cpystrn(user, argv[4], sizeof(user));
        apr_cpystrn(realm, argv[3], sizeof(realm));
        apr_file_printf(errfile, "Adding password for %s in realm %s.\n",
                    user, realm);
        add_password(user, realm, f);
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

    if (apr_file_open(&f, argv[1], APR_READ, APR_OS_DEFAULT, cntxt) != APR_SUCCESS) {
        apr_file_printf(errfile,
                "Could not open passwd file %s for reading.\n", argv[1]);
        apr_file_printf(errfile, "Use -c option to create new one.\n");
        cleanup_tempfile_and_exit(1);
    }
    apr_cpystrn(user, argv[3], sizeof(user));
    apr_cpystrn(realm, argv[2], sizeof(realm));

    found = 0;
    while (!(get_line(line, sizeof(line), f))) {
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
            apr_file_printf(errfile, "Changing password for user %s in realm %s\n",
                    user, realm);
            add_password(user, realm, tfp);
            found = 1;
        }
    }
    if (!found) {
        apr_file_printf(errfile, "Adding user %s in realm %s\n", user, realm);
        add_password(user, realm, tfp);
    }
    apr_file_close(f);

    /* The temporary file has all the data, just copy it to the new location.
     */
    if (apr_file_copy(dirname, argv[1], APR_FILE_SOURCE_PERMS, cntxt) !=
                APR_SUCCESS) {
        apr_file_printf(errfile, "%s: unable to update file %s\n",
                        argv[0], argv[1]);
    }
    apr_file_close(tfp);

    return 0;
}