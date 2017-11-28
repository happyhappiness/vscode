        case '?':
            if (xisprint(optopt)) {
                fprintf(stderr, "Unknown option '-%c'.\n", optopt);
            } else {
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            }
        // fall through to display help texts.

        default:
            usage(argv[0]);
            exit(1);
        }
    }
