            config.interactive = 1;
        } else if (!strcmp(argv[i],"-c")) {
            config.argn_from_stdin = 1;
        } else {
            break;
        }
