                {
                    exit(0);
                } else if (strcasecmp(argv[0],"restart") == 0) {
                    if (config.eval_ldb) {
                        return; /* Return to evalMode to restart the session. */
                    } else {
                        printf("Use 'restart' only in Lua debugging mode.");
