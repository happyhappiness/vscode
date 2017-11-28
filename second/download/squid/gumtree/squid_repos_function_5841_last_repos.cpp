int
main(int argc, char **argv)
{
    char username[256];
    char password[256];
    char wstr[256];
    int err = 0;

    openlog("basic_smb_lm_auth", LOG_PID, LOG_USER);
    setbuf(stdout, NULL);

    for (int j = 1; j < argc; ++j) {
        std::string arg = argv[j];
        size_t pos=arg.find('/');
        if (arg.find('/',pos+1) != std::string::npos) {
            std::cerr << "Error: can't understand domain controller specification '"
                      << arg << "'. Ignoring" << std::endl;
        }
        domaincontroller dc;
        dc.domain = arg.substr(0,pos);
        dc.server = arg.substr(pos+1);
        if (dc.domain.length() == 0 || dc.server.length() == 0) {
            std::cerr << "Error: invalid domain specification in '" << arg <<
                      "'. Ignoring." << std::endl;
            exit(1);
        }
        domaincontrollers.push_back(dc);
    }
    if (domaincontrollers.empty()) {
        display_usage_instructions();
        std::cerr << "Error: no domain controllers specified" << std::endl;
        exit(1);
    }

    while (1) {
        int n;
        /* Read whole line from standard input. Terminate on break. */
        memset(wstr, '\0', sizeof(wstr));
        if (fgets(wstr, 255, stdin) == NULL)
            break;
        /* ignore this line if we didn't get the end-of-line marker */
        if (NULL == strchr(wstr, '\n')) {
            err = 1;
            continue;
        }
        if (err) {
            syslog(LOG_WARNING, "oversized message");
            puts("ERR");
            err = 0;
            continue;
        }

        /*
         * extract username and password.
         */
        username[0] = '\0';
        password[0] = '\0';
        n = sscanf(wstr, "%s %[^\n]", username, password);
        if (2 != n) {
            puts("ERR");
            continue;
        }
        /* Check for invalid or blank entries */
        if ((username[0] == '\0') || (password[0] == '\0')) {
            puts("ERR");
            continue;
        }

        rfc1738_unescape(username);
        rfc1738_unescape(password);

        if (validate_user(username, password)) {
            puts("OK");
        } else {
            syslog(LOG_INFO, "'%s' login failed", username);
            puts("ERR");
        }
        err = 0;
    }

    return 0;
}