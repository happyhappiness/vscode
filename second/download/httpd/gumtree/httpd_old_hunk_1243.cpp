                    posting = 1;
                }
                else if (postdata) {
                    exit(r);
                }
                break;
            case 'r':
                recverrok = 1;
                break;
            case 'v':
                verbosity = atoi(optarg);
                break;
