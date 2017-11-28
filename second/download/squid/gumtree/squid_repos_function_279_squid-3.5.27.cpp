void
process_options(int argc, char *argv[])
{
    int opt;

    opterr = 0;
    while (-1 != (opt = getopt(argc, argv, "D:GPcdh"))) {
        switch (opt) {
        case 'D':
            DefaultDomain = xstrndup(optarg, DNLEN + 1);
            strlwr(DefaultDomain);
            break;
        case 'G':
            use_global = 1;
            break;
        case 'P':
            use_PDC_only = 1;
            break;
        case 'c':
            use_case_insensitive_compare = 1;
            break;
        case 'd':
            debug_enabled = 1;
            break;
        case 'h':
            usage(argv[0]);
            exit(0);
        case '?':
            opt = optopt;
        /* fall thru to default */
        default:
            fprintf(stderr, "%s: FATAL: Unknown option: -%c. Exiting\n", program_name, opt);
            usage(argv[0]);
            exit(1);
            break;      /* not reached */
        }
    }
    return;
}