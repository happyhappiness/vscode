static void
process_options(int argc, char *argv[])
{
    int opt, had_error = 0;

    opterr = 0;
    while (-1 != (opt = getopt(argc, argv, "hd"))) {
        switch (opt) {
        case 'd':
            debug_enabled = 1;
            break;
        case 'h':
            usage();
            exit(0);
        case '?':
            opt = optopt;
        /* fall thru to default */
        default:
            fprintf(stderr, "unknown option: -%c. Exiting\n", opt);
            usage();
            had_error = 1;
        }
    }
    if (had_error)
        exit(1);
}