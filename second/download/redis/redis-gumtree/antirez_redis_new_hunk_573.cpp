                    strcasecmp(argv[0],"exit") == 0)
                {
                    exit(0);
                } else if (strcasecmp(argv[0],"restart") == 0) {
                    if (config.eval_ldb) {
                        return; /* Return to evalMode to restart the session. */
                    } else {
                        printf("Use 'restart' only in Lua debugging mode.");
                    }
                } else if (argc == 3 && !strcasecmp(argv[0],"connect")) {
                    sdsfree(config.hostip);
                    config.hostip = sdsnew(argv[1]);
