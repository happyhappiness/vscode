            fprintf(stderr, "%s: ERROR: Input Too large: %s\n", argv[0], buf);
            while (fgets(buf, sizeof(buf), stdin)) {
                fprintf(stderr, "%s: ERROR: Input Too large..: %s\n", argv[0], buf);
                if (strchr(buf, '\n') != NULL)
                    break;
            }
            SEND_ERR("");
            continue;
        }
        user = strtok(buf, " \n");
        if (!user) {
            debug("%s: Invalid request: No Username given\n", argv[0]);
            SEND_ERR("Invalid request. No Username");
            continue;
        }
        rfc1738_unescape(user);
        if (strip_nt_domain) {
            char *u = strrchr(user, '\\');
            if (!u)
