        case '1':
            ttl = 0;
            break;
        case 'o':
            no_acct_mgmt = 1;
            break;
        case 'r':
            no_realm = 1;
            break;
        default:
            fprintf(stderr, "FATAL: Unknown getopt value '%c'\n", ch);
            usage(argv[0]);
            exit(1);
        }
    }
