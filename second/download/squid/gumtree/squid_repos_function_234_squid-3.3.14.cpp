int main(int argc, char **argv)
{
    char request[HELPER_INPUT_BUFFER];
    int opt;

    program_name = argv[0];

    while ((opt = getopt(argc, argv, "dp:l:b:h")) != -1) {
        switch (opt) {
        case 'd':
            tq_debug_enabled = true;
            break;
        case 'l':
            open_log(optarg);
            break;
        case 'b':
            db_path = optarg;
            break;
        case 'p':
            pauseLength = atoi(optarg);
            break;
        case 'h':
            usage();
            exit(0);
            break;
        }
    }

    log_info("Starting %s\n", __FILE__);
    setbuf(stdout, NULL);

    init_db();

    if ( optind + 1 != argc ) {
        usage();
        exit(1);
    } else {
        readConfig(argv[optind]);
    }

    log_info("Waiting for requests...\n");
    while (fgets(request, HELPER_INPUT_BUFFER, stdin)) {
        // we expect the following line syntax: %LOGIN
        const char *user_key = strtok(request, " \n");
        if (!user_key) {
            SEND_ERR("User name missing");
            continue;
        }
        processActivity(user_key);
    }
    log_info("Ending %s\n", __FILE__);
    shutdown_db();
    return 0;
}