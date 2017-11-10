int main(int argc, const char *const argv[]) {
    int i;
    int rv;
    int list_provided = 0;
    abts_suite *suite = NULL;
   
    initialize();

    quiet = !isatty(STDOUT_FILENO);

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-v")) {
            verbose = 1;
            continue;
        }
        if (!strcmp(argv[i], "-x")) {
            exclude = 1;
            continue;
        }
        if (!strcmp(argv[i], "-l")) {
            list_tests = 1;
            continue;
        }
        if (!strcmp(argv[i], "-q")) {
            quiet = 1;
            continue;
        }
        if (argv[i][0] == '-') {
            fprintf(stderr, "Invalid option: `%s'\n", argv[i]);
            exit(1);
        }
        list_provided = 1;
    }

    if (list_provided) {
        /* Waste a little space here, because it is easier than counting the
         * number of tests listed.  Besides it is at most three char *.
         */
        testlist = calloc(argc + 1, sizeof(char *));
        for (i = 1; i < argc; i++) {
            testlist[i - 1] = argv[i];
        }
    }

    for (i = 0; i < (sizeof(alltests) / sizeof(struct testlist *)); i++) {
        suite = alltests[i].func(suite);
    }

    rv = report(suite);
    return rv;
}