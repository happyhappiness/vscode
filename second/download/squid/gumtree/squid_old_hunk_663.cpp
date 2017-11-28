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
