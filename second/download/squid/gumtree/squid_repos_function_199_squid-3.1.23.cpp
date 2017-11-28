void
process_options(int argc, char *argv[])
{
    int opt, j, had_error = 0;
    dc *new_dc = NULL, *last_dc = NULL;
    while (-1 != (opt = getopt(argc, argv, "bfld"))) {
        switch (opt) {
        case 'b':
            load_balance = 1;
            break;
        case 'f':
            fprintf(stderr,
                    "WARNING. The -f flag is DEPRECATED and always active.\n");
            break;
#ifdef NTLM_FAIL_OPEN
        case 'l':
            last_ditch_enabled = 1;
            break;
#endif
        case 'd':
            debug_enabled=1;
            break;
        default:
            fprintf(stderr, "unknown option: -%c. Exiting\n", opt);
            usage();
            had_error = 1;
        }
    }
    if (had_error)
        exit(1);
    /* Okay, now begin filling controllers up */
    /* we can avoid memcpy-ing, and just reuse argv[] */
    for (j = optind; j < argc; j++) {
        char *d, *c;
        /* d will not be freed in case of non-error. Since we don't reconfigure,
         * it's going to live as long as the process anyways */
        d = malloc(strlen(argv[j]) + 1);
        strcpy(d, argv[j]);
        debug("Adding domain-controller %s\n", d);
        if (NULL == (c = strchr(d, '\\')) && NULL == (c = strchr(d, '/'))) {
            fprintf(stderr, "Couldn't grok domain-controller %s\n", d);
            free(d);
            continue;
        }
        /* more than one delimiter is not allowed */
        if (NULL != strchr(c + 1, '\\') || NULL != strchr(c + 1, '/')) {
            fprintf(stderr, "Broken domain-controller %s\n", d);
            free(d);
            continue;
        }
        *c++ = '\0';
        new_dc = (dc *) malloc(sizeof(dc));
        if (!new_dc) {
            fprintf(stderr, "Malloc error while parsing DC options\n");
            free(d);
            continue;
        }
        /* capitalize */
        uc(c);
        uc(d);
        numcontrollers++;
        new_dc->domain = d;
        new_dc->controller = c;
        new_dc->dead = 0;
        if (controllers == NULL) {	/* first controller */
            controllers = new_dc;
            last_dc = new_dc;
        } else {
            last_dc->next = new_dc;	/* can't be null */
            last_dc = new_dc;
        }
    }
    if (numcontrollers == 0) {
        fprintf(stderr, "You must specify at least one domain-controller!\n");
        usage();
        exit(1);
    }
    last_dc->next = controllers;	/* close the queue, now it's circular */
}