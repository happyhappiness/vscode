            load_balance = 1;
            break;
        case 'f':
            fprintf(stderr,
                    "WARNING. The -f flag is DEPRECATED and always active.\n");
            break;
        case 'd':
            debug_enabled=1;
            break;
        default:
            fprintf(stderr, "unknown option: -%c. Exiting\n", opt);
            usage();
