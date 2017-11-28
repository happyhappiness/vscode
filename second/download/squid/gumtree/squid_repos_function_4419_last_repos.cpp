int main(int argc, char **argv)
{
    char request[HELPER_INPUT_BUFFER];
    int opt;
    int default_action = 1;

    program_name = argv[0];

    while ((opt = getopt(argc, argv, "t:T:b:a?")) != -1) {
        switch (opt) {
        case 'T':
            fixed_timeout = 1;
        case 't':
            session_ttl = strtol(optarg, NULL, 0);
            break;
        case 'b':
            db_path = optarg;
            break;
        case 'a':
            default_action = 0;
            break;
        case '?':
            usage();
            exit(0);
            break;
        }
    }

    setbuf(stdout, NULL);

    init_db();

    while (fgets(request, HELPER_INPUT_BUFFER, stdin)) {
        int action = 0;
        const char *channel_id = strtok(request, " ");
        char *detail = strtok(NULL, "\n");
        if (detail == NULL) {
            // Only 1 paramater supplied. We are expecting at least 2 (including the channel ID)
            fprintf(stderr, "FATAL: %s is concurrent and requires the concurrency option to be specified.\n", program_name);
            shutdown_db();
            exit(1);
        }
        char *lastdetail = strrchr(detail, ' ');
        size_t detail_len = strlen(detail);
        if (lastdetail) {
            if (strcmp(lastdetail, " LOGIN") == 0) {
                action = 1;
                detail_len = (size_t)(lastdetail-detail);
                *lastdetail = '\0';
            } else if (strcmp(lastdetail, " LOGOUT") == 0) {
                action = -1;
                detail_len = (size_t)(lastdetail-detail);
                *lastdetail = '\0';
            } else if (!default_action && strcmp(lastdetail, " -") == 0) {
                // no action; LOGIN/LOGOUT not supplied
                // but truncate the '-' %DATA value given by Squid-4 and later
                detail_len = (size_t)(lastdetail-detail);
                *lastdetail = '\0';
            }
        }
        if (action == -1) {
            session_logout(detail, detail_len);
            printf("%s OK message=\"Bye\"\n", channel_id);
        } else if (action == 1) {
            session_login(detail, detail_len);
            printf("%s OK message=\"Welcome\"\n", channel_id);
        } else if (session_active(detail, detail_len)) {
            if (fixed_timeout == 0) {
                session_login(detail, detail_len);
            }
            printf("%s OK\n", channel_id);
        } else if (default_action == 1) {
            session_login(detail, detail_len);
            printf("%s ERR message=\"Welcome\"\n", channel_id);
        } else {
            printf("%s ERR message=\"No session available\"\n", channel_id);
        }
    }
    shutdown_db();
    return 0;
}