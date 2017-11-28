int main(int argc, char **argv)
{
    char request[256];
    int opt;
    int default_action = 1;

    program_name = argv[0];

    while ((opt = getopt(argc, argv, "t:b:a?")) != -1) {
        switch (opt) {
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

    while (fgets(request, sizeof(request), stdin)) {
        const char *user_key, *detail;
        char *lastdetail;
        int action = 0;
        user_key = strtok(request, " \n");
        detail = strtok(NULL, "\n");
        lastdetail = strrchr(detail, ' ');
        if (lastdetail) {
            if (strcmp(lastdetail, " LOGIN") == 0) {
                *lastdetail++ = '\0';
                action = 1;
            } else if (strcmp(lastdetail, " LOGOUT") == 0) {
                action = -1;
                *lastdetail++ = '\0';
            }
        }
        if (action == -1) {
            session_logout(detail);
            printf("%s OK message=\"Bye\"\n", user_key);
        } else if (action == 1) {
            session_login(detail);
            printf("%s OK message=\"Welcome\"\n", user_key);
        } else if (session_active(detail)) {
            session_login(detail);
            printf("%s OK\n", user_key);
        } else if (default_action == 1) {
            session_login(detail);
            printf("%s ERR message=\"Welcome\"\n", user_key);
        } else {
            printf("%s ERR message=\"No session available\"\n", user_key);
        }
    }
    shutdown_db();
    return 0;
}