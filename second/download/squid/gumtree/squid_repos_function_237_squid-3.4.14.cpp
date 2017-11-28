int
main(int argc, char *argv[])
{
    char *user, *suser, *p;
    char buf[HELPER_INPUT_BUFFER];
    char **grents = NULL;
    int check_pw = 0, ch, ngroups = 0, i, j = 0, strip_dm = 0;

    /* make standard output line buffered */
    setvbuf(stdout, NULL, _IOLBF, 0);

    /* get user options */
    while ((ch = getopt(argc, argv, "dspg:")) != -1) {
        switch (ch) {
        case 'd':
            debug_enabled = 1;
            break;
        case 's':
            strip_dm = 1;
            break;
        case 'p':
            check_pw = 1;
            break;
        case 'g':
            grents = (char**)realloc(grents, sizeof(*grents) * (ngroups+1));
            grents[ngroups] = optarg;
            ++ngroups;
            break;
        case '?':
            if (xisprint(optopt)) {
                fprintf(stderr, "Unknown option '-%c'.\n", optopt);
            } else {
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            }
            // fall through to display help texts.

        default:
            usage(argv[0]);
            exit(1);
        }
    }
    if (optind < argc) {
        fprintf(stderr, "FATAL: Unknown option '%s'\n", argv[optind]);
        usage(argv[0]);
        exit(1);
    }
    while (fgets(buf, HELPER_INPUT_BUFFER, stdin)) {
        j = 0;
        if ((p = strchr(buf, '\n')) == NULL) {
            /* too large message received.. skip and deny */
            fprintf(stderr, "ERROR: %s: Too large: %s\n", argv[0], buf);
            while (fgets(buf, sizeof(buf), stdin)) {
                fprintf(stderr, "ERROR: %s: Too large..: %s\n", argv[0], buf);
                if (strchr(buf, '\n') != NULL)
                    break;
            }
            SEND_ERR("Username Input too large.");
            continue;
        }
        *p = '\0';
        if ((p = strtok(buf, " ")) == NULL) {
            SEND_ERR("No username given.");
            continue;
        } else {
            user = p;
            rfc1738_unescape(user);
            if (strip_dm) {
                suser = strchr(user, '\\');
                if (!suser) suser = strchr(user, '/');
                if (suser && suser[1]) user = suser + 1;
            }
            /* check groups supplied by Squid */
            while ((p = strtok(NULL, " ")) != NULL) {
                rfc1738_unescape(p);
                if (check_pw == 1)
                    j += validate_user_pw(user, p);
                j += validate_user_gr(user, p);
            }
        }

        /* check groups supplied on the command line */
        for (i = 0; i < ngroups; ++i) {
            if (check_pw == 1) {
                j += validate_user_pw(user, grents[i]);
            }
            j += validate_user_gr(user, grents[i]);
        }

        if (j > 0) {
            SEND_OK("");
        } else {
            SEND_ERR("");
        }
    }
    return 0;
}