                csvperc = strdup(optarg);
                break;
            case 'S':
                confidence = 0;
                break;
            case 'p':
                if (method != NO_METH)
                    err("Cannot mix POST with other methods\n");
                if ((status = open_postfile(optarg)) != APR_SUCCESS) {
                    exit(1);
                }
                method = POST;
                send_body = 1;
                break;
            case 'u':
                if (method != NO_METH)
                    err("Cannot mix PUT with other methods\n");
                if ((status = open_postfile(optarg)) != APR_SUCCESS) {
                    exit(1);
                }
                method = PUT;
                send_body = 1;
                break;
            case 'r':
                recverrok = 1;
                break;
            case 'v':
                verbosity = atoi(optarg);
